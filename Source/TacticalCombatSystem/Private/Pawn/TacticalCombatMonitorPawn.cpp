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

void ATacticalCombatMonitorPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	UE_LOG(LogTemp, Warning, TEXT("ATacticalCombatMonitorPawn::PossessedBy, NewController Name: %s"), *NewController->GetName());
}

void ATacticalCombatMonitorPawn::ZoomIn_Implementation()
{
	// 取得目前攝影機臂長度
	const float CurrentTargetArmLength = MonitorSpringArm->TargetArmLength;
	// 放大會將鏡頭拉近，也就相當於縮短攝影機臂長度
	MonitorSpringArm->TargetArmLength = FMath::Clamp(CurrentTargetArmLength - ZoomUnit, MinTargetArmLength, MaxTargetArmLength);
	UE_LOG(LogTemp, Warning, TEXT("ATacticalCombatMonitorPawn::ZoomIn"));
}

void ATacticalCombatMonitorPawn::ZoomOut_Implementation()
{
	// 取得目前攝影機臂長度
	const float CurrentTargetArmLength = MonitorSpringArm->TargetArmLength;
	MonitorSpringArm->TargetArmLength = FMath::Clamp(CurrentTargetArmLength + ZoomUnit, MinTargetArmLength, MaxTargetArmLength);
	// 縮小會將鏡頭拉遠，也就相當於拉長攝影機臂長度
	UE_LOG(LogTemp, Warning, TEXT("ATacticalCombatMonitorPawn::ZoomOut"));
}

