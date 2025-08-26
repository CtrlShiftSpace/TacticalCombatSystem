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
}

void ATacticalCombatMonitorPawn::BeginPlay()
{
	Super::BeginPlay();
	// 取得預設的攝影機臂長
	DefaultSpringArmLength = MonitorSpringArm->TargetArmLength;

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

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(ForwardDirection, MoveVector.Y);
	AddMovementInput(RightDirection, MoveVector.X);
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

float ATacticalCombatMonitorPawn::GetScaleSpringArmLength(const float InZoomScale) const
{
	if (InZoomScale <= 0.f)
	{
		return DefaultSpringArmLength / FMath::Clamp(ZoomScale, MinZoomScale, MaxZoomScale);
	}
	// 倍率大小與攝影機臂長成反比，故使用除法計算
	return DefaultSpringArmLength / FMath::Clamp(InZoomScale, MinZoomScale, MaxZoomScale);
}

