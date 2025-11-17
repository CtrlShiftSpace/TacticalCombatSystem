// Copyright  CtrlShiftSpace


#include "Character/TactCombCharacter.h"

#include "AbilitySystem/TactCombAbilitySystemComponent.h"
#include "AbilitySystem/TactCombAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/TactCombPlayerState.h"

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

	// 取消自動指派 AI Controller 
	AutoPossessAI = EAutoPossessAI::Disabled;

	AbilitySystemComponent = CreateDefaultSubobject<UTactCombAbilitySystemComponent>("AbilitySystemComponent");
	// 設定一致server 與 client的狀態會同步
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UTactCombAttributeSet>("AttributeSet");
}

void ATactCombCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

int32 ATactCombCharacter::GetCharacterLevel_Implementation()
{
	const ATactCombPlayerState* TactCombPlayerState = GetTactCombPlayerState();
	const FPlayerAbilityInfo& PlayerAbilityInfo = TactCombPlayerState->GetTargetPlayerAbilityInfo(this);
	return PlayerAbilityInfo.PlayerLevel;
}

FPlayerAbilityInfo ATactCombCharacter::GetPlayerAbilityInfo_Implementation() const
{
	FPlayerAbilityInfo PlayerAbilityInfo;
	PlayerAbilityInfo.ASC = AbilitySystemComponent;
	PlayerAbilityInfo.AS = AttributeSet;
	// TODO: 暫時先寫死，後續要改用讀取變數
	PlayerAbilityInfo.PlayerLevel = 1;
	return PlayerAbilityInfo;
}

void ATactCombCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();
	InitAttributes();
}

void ATactCombCharacter::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();

	// 取得 Player State
	ATactCombPlayerState* TactCombPlayerState = GetTactCombPlayerState();
	if (!IsValid(TactCombPlayerState))
	{
		UE_LOG(LogTemp, Warning, TEXT("TactCombPlayerState is not valid."));
		return;
	}

	// 讓 Player State 知道玩家角色已建立
	TactCombPlayerState->OnPlayerCharacterSetup.Broadcast(this);
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

ATactCombPlayerState* ATactCombCharacter::GetTactCombPlayerState() const
{
	// 先透過繼承的方法，嘗試取得 Player State，但僅限此 Character 正處於 possess 的狀態才能取到
	APlayerState* CharacterPlayerState = GetPlayerState<APlayerState>();
	if (!IsValid(CharacterPlayerState))
	{
		// 如果未取得 Player State 則改為透過 Player Controller 呼叫
		if (const APlayerController* CharacterPlayerController = GetWorld()->GetFirstPlayerController())
		{
			// 嘗試取得 Player Controller 中的 Player State
			CharacterPlayerState = CharacterPlayerController->GetPlayerState<APlayerState>();
			if (!IsValid(CharacterPlayerState))
			{
				UE_LOG(LogTemp, Warning, TEXT("%s is not valid player state."), *GetName());
				return nullptr;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is not valid player controller."), *GetName());
			return nullptr;
		}
	}

	// 轉換為 ATactCombPlayerState 類別
	return Cast<ATactCombPlayerState>(CharacterPlayerState);
}
