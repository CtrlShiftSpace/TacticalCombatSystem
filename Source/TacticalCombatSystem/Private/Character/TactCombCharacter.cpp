// Copyright  CtrlShiftSpace


#include "Character/TactCombCharacter.h"

#include "Game/TactCombGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ATactCombCharacter::ATactCombCharacter() : Super()
{

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

	if (bGridMoveMode)
	{
		if (MoveVector.Y != 0.f)
		{
			const bool bPositive = MoveVector.Y > 0.f;
			FVector ForwardDirection = FVector(MoveUnit, 0.f, 0.f);
			if (!bPositive)
			{
				ForwardDirection.X *= -1.f;
			}
			AddMovementInput(ForwardDirection);
		}
		if (MoveVector.X != 0.f)
		{
			const bool bPositive = MoveVector.X > 0.f;
			FVector RightDirection = FVector(0.f, MoveUnit, 0.f);
			if (!bPositive)
			{
				RightDirection.Y *= -1.f;
			}
			AddMovementInput(RightDirection);
		}
	}
	else
	{
		// 設定移動位置
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MoveVector.Y);
		AddMovementInput(RightDirection, MoveVector.X);
	}
}

void ATactCombCharacter::AssignRotate_Implementation(const FRotator& Rotator)
{
	
}
