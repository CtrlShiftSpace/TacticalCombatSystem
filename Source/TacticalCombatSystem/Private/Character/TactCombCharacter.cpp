// Copyright  CtrlShiftSpace


#include "Character/TactCombCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATactCombCharacter::ATactCombCharacter() : Super()
{
	// 建立攝影機臂
	CharSprArm = CreateDefaultSubobject<USpringArmComponent>("CharSprArm");
	CharSprArm->bInheritPitch = false;
	CharSprArm->bInheritRoll = false;
	CharSprArm->bInheritYaw = false;
	CharSprArm->SetUsingAbsoluteRotation(true);
	CharSprArm->bDoCollisionTest = false;
	CharSprArm->SetupAttachment(GetCapsuleComponent(), "CharSprArm");

	// 建立攝影機(建立在攝影機臂上)
	CharCam = CreateDefaultSubobject<UCameraComponent>("CharCamera");
	CharCam->SetupAttachment(CharSprArm);
	// 攝影機不跟著轉動
	CharCam->bUsePawnControlRotation = false;
	
	// 設定角色移動面對方向也會跟著移動
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// 跳的力量
	GetCharacterMovement()->JumpZVelocity = 700.f;

	// 取消預設的旋轉朝向
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
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
	const FRotator Rotation = GetControlRotation();
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

void ATactCombCharacter::Jump_Implementation()
{
	// 呼叫 ACharacter 的 Jump
	Super::Jump();
}
