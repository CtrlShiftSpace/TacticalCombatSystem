// Copyright  CtrlShiftSpace


#include "Pawn/TactCombMonitorPawn.h"

#include "AbilitySystem/TactCombAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/TactCombPlayerController.h"
#include "Player/TactCombPlayerState.h"
#include "UI/HUD/TactCombHUD.h"

// Sets default values
ATactCombMonitorPawn::ATactCombMonitorPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	MonitorSpringArm = CreateDefaultSubobject<USpringArmComponent>("MonitorSpringArm");
	MonitorSpringArm->SetupAttachment(RootComponent);
	MonitorSpringArm->bDoCollisionTest = false;

	MonitorCamera = CreateDefaultSubobject<UCameraComponent>("MonitorCamera");
	MonitorCamera->SetupAttachment(MonitorSpringArm);
	MonitorCamera->bUsePawnControlRotation = false;

	// 建立 Timeline 元件
	ZoomTimelineComponent = CreateDefaultSubobject<UTimelineComponent>("ZoomTimelineComponent");
	MoveTimelineComponent = CreateDefaultSubobject<UTimelineComponent>("MoveTimelineComponent");
	RotateTimelineComponent = CreateDefaultSubobject<UTimelineComponent>("RotateTimelineComponent");
}

void ATactCombMonitorPawn::BeginPlay()
{
	Super::BeginPlay();
	// 取得預設的攝影機臂長
	DefaultSpringArmLength = MonitorSpringArm->TargetArmLength;
	DefaultMonitorRotator = GetActorRotation();
	
	if (IsValid(MonitorZoomCurve))
	{
		// 建立旋轉的 Timeline 參數與事件
		FTactCombFloatTimelineEvent ZoomTimelineEvent;
		ZoomTimelineEvent.Curve = MonitorZoomCurve;
		// 綁定 Delegate 要執行的函式
		ZoomTimelineEvent.InterpDelegate.BindUObject(this, &ThisClass::ZoomInterpEvent);
		ZoomTimelineEvent.FinishedDelegate.BindUObject(this, &ThisClass::ZoomFinishedEvent);
		AssignTactCombFloatTimelineComponent(*ZoomTimelineComponent, ZoomTimelineEvent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MonitorZoomCurve is not valid"));
	}

	if (IsValid(MonitorZoomCurve))
	{
		// 建立移動的 Timeline 參數與事件
		FTactCombFloatTimelineEvent MoveTimelineEvent;
		MoveTimelineEvent.Curve = MonitorZoomCurve;
		// 綁定 Delegate 要執行的函式
		MoveTimelineEvent.InterpDelegate.BindUObject(this, &ThisClass::MoveInterpEvent);
		MoveTimelineEvent.FinishedDelegate.BindUObject(this, &ThisClass::MoveFinishedEvent);
		AssignTactCombFloatTimelineComponent(*MoveTimelineComponent, MoveTimelineEvent);
	}

	if (IsValid(MonitorRotateCurve))
	{
		// 建立旋轉的 Timeline 參數與事件
		FTactCombFloatTimelineEvent RotateTimelineEvent;
		RotateTimelineEvent.Curve = MonitorRotateCurve;
		// 綁定 Delegate 要執行的函式
		RotateTimelineEvent.InterpDelegate.BindUObject(this, &ThisClass::RotateYawInterpEvent);
		RotateTimelineEvent.FinishedDelegate.BindUObject(this, &ThisClass::RotateFinishedEvent);
		AssignTactCombFloatTimelineComponent(*RotateTimelineComponent, RotateTimelineEvent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MonitorRotateCurve is not valid"));
	}
}

void ATactCombMonitorPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 建立 Viewport UI
	InitialViewport();
	UE_LOG(LogTemp, Warning, TEXT("ATactCombMonitorPawn::PossessedBy, NewController Name: %s"), *NewController->GetName());
}

void ATactCombMonitorPawn::ZoomIn_Implementation()
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

void ATactCombMonitorPawn::ZoomOut_Implementation()
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

void ATactCombMonitorPawn::AssignMovement_Implementation(const FVector& MoveVector)
{
	const FRotator Rotation = GetActorRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * MoveVector.Y;
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * MoveVector.X;

	// 取得移動目標方向
	const FVector TargetDirection = (ForwardDirection + RightDirection).GetSafeNormal();
	const FVector MoveLocation = GetActorLocation() + TargetDirection * MoveSpeed;
	// 移動至新的位置
	LocationChanged(MoveLocation);
}

void ATactCombMonitorPawn::AssignRotate_Implementation(const FRotator& Rotator)
{
	// 過濾掉沒有旋轉的情況
	if (Rotator.IsZero())
	{
		return;
	}
	RotatorChanged(Rotator);
}

void ATactCombMonitorPawn::ZoomScaleChanged(const float InZoomScale)
{
	// 檢查縮放曲線是否有效
	if (!IsValid(MonitorZoomCurve))
	{
		return;
	}
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
	ZoomTimelineComponent->PlayFromStart();
}

void ATactCombMonitorPawn::LocationChanged(const FVector& InLocation)
{
	// 檢查移動曲線是否有效
	if (!IsValid(MonitorMoveCurve))
	{
		return;
	}
	// 正在移動過程中要等執行完畢才能進行下一次移動
	if (bMoving)
	{
		return;
	}
	bMoving = true;
	// 取得移動前的位置
	BeforeLocation = GetActorLocation();
	// 計算傳入位置與目前位置的差距
	OffsetLocation = InLocation - BeforeLocation;
	MoveTimelineComponent->PlayFromStart();
}

void ATactCombMonitorPawn::RotatorChanged(const FRotator& InRotator)
{
	// 檢查旋轉曲線是否有效
	if (!IsValid(MonitorRotateCurve))
	{
		return;
	}
	// 正在旋轉過程中要等執行完畢才能進行下一次旋轉
	if (bRotating)
	{
		return;
	}
	
	bRotating = true;
	// 取得旋轉前的 Yaw
	BeforeYaw = GetActorRotation().Yaw;
	// 計算傳入 Yaw 與目前 Yaw 的差距
	OffsetYaw = InRotator.Yaw;
	RotateTimelineComponent->PlayFromStart();
}

void ATactCombMonitorPawn::AssignTactCombFloatTimelineComponent(UTimelineComponent& TactCombTimelineComponent, const FTactCombFloatTimelineEvent& TactCombFloatTimelineEvent)
{
	// 綁定 Delegate 要執行的函式
	TactCombTimelineComponent.AddInterpFloat(TactCombFloatTimelineEvent.Curve, TactCombFloatTimelineEvent.InterpDelegate);
	TactCombTimelineComponent.SetTimelineFinishedFunc(TactCombFloatTimelineEvent.FinishedDelegate);
	TactCombTimelineComponent.SetLooping(false);
	TactCombTimelineComponent.SetPlayRate(1.f);
	// 設定 Timeline 的長度為最後一個 keyframe，也就是 X 軸的位置
	TactCombTimelineComponent.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
}

UAbilitySystemComponent* ATactCombMonitorPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ATactCombMonitorPawn::GetAttributeSet() const
{
	return AttributeSet;
}

float ATactCombMonitorPawn::GetZoomScale() const
{
	return ZoomScale;
}

void ATactCombMonitorPawn::SetZoomScale(const float InZoomScale)
{
	ZoomScale = FMath::Clamp(InZoomScale, MinZoomScale, MaxZoomScale);
	MonitorSpringArm->TargetArmLength = GetScaleSpringArmLength(ZoomScale);
}

float ATactCombMonitorPawn::GetOffsetZoomScale(const float InZoomScale) const
{
	return InZoomScale - ZoomScale;
}

float ATactCombMonitorPawn::GetOffsetYaw(const float InYaw) const
{
	return InYaw - BeforeYaw;
}

void ATactCombMonitorPawn::ZoomInterpEvent(const float InterpValue)
{
	SetZoomScale(BeforeZoomScale + InterpValue * OffsetZoomScale);
}

void ATactCombMonitorPawn::ZoomFinishedEvent()
{
	bZooming = false;
}

void ATactCombMonitorPawn::MoveInterpEvent(const float InterpValue)
{
	// 計算本次要移動到的位置
	const FVector InterpLocation = BeforeLocation + OffsetLocation * InterpValue;
	SetActorLocation(InterpLocation);
}

void ATactCombMonitorPawn::MoveFinishedEvent()
{
	bMoving = false;
}

void ATactCombMonitorPawn::RotateYawInterpEvent(const float InterpValue)
{
	// 取得插值的旋轉位置
	FRotator InterpRotator = GetActorRotation();
	// 計算本次要旋轉到的 Yaw 位置
	InterpRotator.Yaw = BeforeYaw + OffsetYaw * InterpValue;
	SetActorRotation(InterpRotator);
}

void ATactCombMonitorPawn::RotateFinishedEvent()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("RotateFinishedEvent"));
	bRotating = false;
}

void ATactCombMonitorPawn::InitialAbilityInfo()
{
	
}

void ATactCombMonitorPawn::InitialViewport()
{
	ATactCombPlayerState* TactCombPlayerState = GetPlayerState<ATactCombPlayerState>();
	check(TactCombPlayerState);
	AbilitySystemComponent = TactCombPlayerState->GetAbilitySystemComponent();
	// Cast<UTactCombAbilitySystemComponent>(TactCombPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	// AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	AttributeSet = TactCombPlayerState->GetAttributeSet();

	// 執行HUD的InitOverlay
	if (ATactCombPlayerController* TactCombPlayerController = Cast<ATactCombPlayerController>(GetController())) {
		// 之所以加 if 是為了處理多人玩家中其他玩家會是nullptr而不用執行以下內容，
		if (ATactCombHUD* TactCombHUD = Cast<ATactCombHUD>(TactCombPlayerController->GetHUD()))
		{
			TactCombHUD->InitViewport(TactCombPlayerController, TactCombPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

float ATactCombMonitorPawn::GetScaleSpringArmLength(const float InZoomScale) const
{
	if (InZoomScale <= 0.f)
	{
		return DefaultSpringArmLength / FMath::Clamp(ZoomScale, MinZoomScale, MaxZoomScale);
	}
	// 倍率大小與攝影機臂長成反比，故使用除法計算
	return DefaultSpringArmLength / FMath::Clamp(InZoomScale, MinZoomScale, MaxZoomScale);
}

