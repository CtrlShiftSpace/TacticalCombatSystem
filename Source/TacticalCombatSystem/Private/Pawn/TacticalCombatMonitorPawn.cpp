// Copyright  CtrlShiftSpace


#include "Pawn/TacticalCombatMonitorPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATacticalCombatMonitorPawn::ATacticalCombatMonitorPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	MonitorSpringArm = CreateDefaultSubobject<USpringArmComponent>("MonitorSpringArm");
	MonitorSpringArm->SetupAttachment(RootComponent);
	MonitorSpringArm->bDoCollisionTest = false;

	MonitorCamera = CreateDefaultSubobject<UCameraComponent>("MonitorCamera");
	MonitorCamera->SetupAttachment(MonitorSpringArm);
	MonitorCamera->bUsePawnControlRotation = false;

	// 建立 Timeline 元件
	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>("TimelineComponent");
	RotateTimelineComponent = CreateDefaultSubobject<UTimelineComponent>("RotateTimelineComponent");
}

void ATacticalCombatMonitorPawn::BeginPlay()
{
	Super::BeginPlay();
	// 取得預設的攝影機臂長
	DefaultSpringArmLength = MonitorSpringArm->TargetArmLength;
	DefaultMonitorRotator = GetActorRotation();

	// Timeline 要執行的動作
	ZoomInterp.BindLambda([this](const float InterpValue)
	{
		SetZoomScale(BeforeZoomScale + InterpValue * OffsetZoomScale);
	});

	// 綁定 Timeline 完成縮放後的動作
	ZoomFinished.BindLambda(
		[this]()
		{
			bZooming = false;
		}
	);
	
	if (IsValid(MonitorCurve))
	{
		TimelineComponent->AddInterpFloat(MonitorCurve, ZoomInterp);
		TimelineComponent->SetTimelineFinishedFunc(ZoomFinished);
		TimelineComponent->SetLooping(false);
		TimelineComponent->SetPlayRate(1.f);
		// 設定 Timeline 的長度為最後一個 keyframe，也就是 X 軸的位置
		TimelineComponent->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	}

	// 建立旋轉的 Timeline 處理
	// RotateCurveEvent.Curve = MonitorCurve;
	FTactCombFloatTimelineEvent RotateTimelineEvent;
	// 綁定 Delegate 要執行的函式
	// RotateInterpDelegate.BindUObject(this, &ThisClass::RotateYawInterpEvent);
	// RotateFinishedDelegate.BindUObject(this, &ThisClass::RotateFinishedEvent);
	// 將參數加入 struct 中
	RotateTimelineEvent.Curve = MonitorCurve;
	RotateTimelineEvent.InterpDelegate.BindLambda([this](const float InterpValue)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("RotateInterpEvent: %f"), InterpValue));
	});

	// RotateTimelineEvent.InterpDelegate.BindUObject(this, &ThisClass::RotateYawInterpEvent);
	RotateTimelineEvent.FinishedDelegate.BindUObject(this, &ThisClass::RotateFinishedEvent);
	// RotateTimelineComponent = CreateTactCombFloatTimelineComponent(FName("RotateTimelineComponent"), RotateTimelineEvent);
	AssignTactCombFloatTimelineComponent(*RotateTimelineComponent.Get(), RotateTimelineEvent);
}

void ATacticalCombatMonitorPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	UE_LOG(LogTemp, Warning, TEXT("ATacticalCombatMonitorPawn::PossessedBy, NewController Name: %s"), *NewController->GetName());
}

void ATacticalCombatMonitorPawn::ZoomIn_Implementation()
{
	// 新的縮放倍率
	const float NewZoomScale = FMath::Clamp(ZoomScale + ZoomScaleUnit, MinZoomScale, MaxZoomScale);
	if (ZoomScale == NewZoomScale)
	{
		return;
	}
	// 設定新的縮放倍率
	ZoomScaleChanged(NewZoomScale);
}

void ATacticalCombatMonitorPawn::ZoomOut_Implementation()
{
	// 新的縮放倍率
	const float NewZoomScale = FMath::Clamp(ZoomScale - ZoomScaleUnit, MinZoomScale, MaxZoomScale);
	if (ZoomScale == NewZoomScale)
	{
		return;
	}
	// 設定新的縮放倍率
	ZoomScaleChanged(NewZoomScale);
}

void ATacticalCombatMonitorPawn::AssignMovement_Implementation(const FVector& MoveVector)
{
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * MoveVector.Y;
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * MoveVector.X;

	// 取得移動目標方向
	const FVector TargetDirection = (ForwardDirection + RightDirection).GetSafeNormal();

	const FVector NextLocation = GetActorLocation() + TargetDirection * MoveSpeed;
	SetActorLocation(NextLocation);
}

void ATacticalCombatMonitorPawn::AssignRotate_Implementation(const FRotator& Rotator)
{
	if (bRotating)
	{
		return;
	}
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("AssignRotate_Implementation: %s"), *Rotator.ToString()));

	bRotating = true;
	// 取得旋轉前的 Yaw
	BeforeYaw = GetActorRotation().Yaw;
	// 計算傳入 Yaw 與目前 Yaw 的差距
	OffsetRotator = Rotator.Yaw;
	RotateTimelineComponent->PlayFromStart();
}

void ATacticalCombatMonitorPawn::ZoomScaleChanged(const float InZoomScale)
{
	// 正在縮放過程中要等執行完畢才能進行下一次縮放
	if (bZooming)
	{
		return;
	}
	bZooming = true;
	// 計算傳入倍率與目前倍率的差距
	OffsetZoomScale = GetOffsetZoomScale(InZoomScale);
	// 紀錄進行縮放前的倍率
	BeforeZoomScale = ZoomScale;
	TimelineComponent->PlayFromStart();
}

void ATacticalCombatMonitorPawn::RotatorChanged(const FRotator& InRotator)
{
	
}

void ATacticalCombatMonitorPawn::AssignTactCombFloatTimelineComponent(UTimelineComponent& TactCombTimelineComponent, const FTactCombFloatTimelineEvent& TactCombFloatTimelineEvent)
{
	// 綁定 Delegate 要執行的函式
	TactCombTimelineComponent.AddInterpFloat(TactCombFloatTimelineEvent.Curve, TactCombFloatTimelineEvent.InterpDelegate);
	TactCombTimelineComponent.SetTimelineFinishedFunc(TactCombFloatTimelineEvent.FinishedDelegate);
	TactCombTimelineComponent.SetLooping(false);
	TactCombTimelineComponent.SetPlayRate(1.f);
	// 設定 Timeline 的長度為最後一個 keyframe，也就是 X 軸的位置
	TactCombTimelineComponent.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
}

float ATacticalCombatMonitorPawn::GetZoomScale() const
{
	return ZoomScale;
}

void ATacticalCombatMonitorPawn::SetZoomScale(const float InZoomScale)
{
	ZoomScale = FMath::Clamp(InZoomScale, MinZoomScale, MaxZoomScale);
	MonitorSpringArm->TargetArmLength = GetScaleSpringArmLength(ZoomScale);
}

float ATacticalCombatMonitorPawn::GetOffsetZoomScale(const float InZoomScale) const
{
	return InZoomScale - ZoomScale;
}

float ATacticalCombatMonitorPawn::GetOffsetYaw(const float InYaw) const
{
	return InYaw - BeforeYaw;
}

void ATacticalCombatMonitorPawn::RotateYawInterpEvent(const float InYaw)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("RotateInterpEvent: %f"), InYaw));
}

void ATacticalCombatMonitorPawn::RotateFinishedEvent()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("RotateFinishedEvent"));
	bRotating = false;
}

float ATacticalCombatMonitorPawn::GetScaleSpringArmLength(const float InZoomScale) const
{
	if (InZoomScale <= 0.f)
	{
		return DefaultSpringArmLength / FMath::Clamp(ZoomScale, MinZoomScale, MaxZoomScale);
	}
	// 倍率大小與攝影機臂長成反比，故使用除法計算
	return DefaultSpringArmLength / FMath::Clamp(InZoomScale, MinZoomScale, MaxZoomScale);
}

