// Copyright  CtrlShiftSpace


#include "Pawn/TacticalCombatMonitorPawn.h"
#include "Camera/CameraComponent.h"
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
}

void ATacticalCombatMonitorPawn::BeginPlay()
{
	Super::BeginPlay();
	// 取得預設的攝影機臂長
	DefaultSpringArmLength = MonitorSpringArm->TargetArmLength;
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

