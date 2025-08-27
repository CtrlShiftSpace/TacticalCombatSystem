// Copyright  CtrlShiftSpace


#include "Player/TacticalCombatPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TacticalCombatGameplayTags.h"
#include "Input/TacticalCombatEnhInputComponent.h"
#include "Interaction/CameraInterface.h"
#include "Interaction/MovementInterface.h"

ATacticalCombatPlayerController::ATacticalCombatPlayerController()
{
	bReplicates = true;
}

void ATacticalCombatPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 顯示滑鼠游標
	bShowMouseCursor = true;
	// 設定預設滑鼠游標
	DefaultMouseCursor = EMouseCursor::Default;

	// 確保輸入Mapping Context 已經被設定
	check(TactCombContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(TactCombContext, 0);
	}

	// 遊戲與UI的輸入模式
	FInputModeGameAndUI InputModeData;
	// 設定相關滑鼠行為
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ATacticalCombatPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UTacticalCombatEnhInputComponent* TacticalCombatEnhInputComponent = CastChecked<UTacticalCombatEnhInputComponent>(InputComponent);
	// 綁定輸入移動行為
	TacticalCombatEnhInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	TacticalCombatEnhInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ATacticalCombatPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector MoveVector = InputActionValue.Get<FVector>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (ControlledPawn->Implements<UMovementInterface>())
		{
			IMovementInterface::Execute_AssignMovement(ControlledPawn, MoveVector);
		}
	}
}

void ATacticalCombatPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// 確認角色是否實作了 CameraInterface
		if (ControlledPawn->Implements<UCameraInterface>())
		{
			// 根據輸入標籤來決定是放大還是縮小
			if (InputTag.MatchesTagExact(FTacticalCombatGameplayTags::Get().InputTag_Zoom_In))
			{
				// 放大
				ICameraInterface::Execute_ZoomIn(ControlledPawn);
			}
			else
			{
				if (InputTag.MatchesTagExact(FTacticalCombatGameplayTags::Get().InputTag_Zoom_Out))
				{
					// 縮小
					ICameraInterface::Execute_ZoomOut(ControlledPawn);
				}
			}
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed: %s"), *InputTag.ToString());
}

void ATacticalCombatPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
}

void ATacticalCombatPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
}
