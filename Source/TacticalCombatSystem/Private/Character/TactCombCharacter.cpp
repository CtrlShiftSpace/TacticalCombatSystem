// Copyright  CtrlShiftSpace


#include "Character/TactCombCharacter.h"

ATactCombCharacter::ATactCombCharacter() : Super()
{
	GridInstComponent = CreateDefaultSubobject<UChildActorComponent>("GridInst");
	GridInstComponent->SetupAttachment(RootComponent);
}

void ATactCombCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ATactCombCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATactCombCharacter::AssignMovement_Implementation(const FVector& MoveVector)
{
	// 取得角色旋轉角度
	const FRotator Rotation = GetActorRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	// 設定移動位置
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, MoveVector.Y);
	AddMovementInput(RightDirection, MoveVector.X);
}

void ATactCombCharacter::AssignRotate_Implementation(const FRotator& Rotator)
{
	
}
