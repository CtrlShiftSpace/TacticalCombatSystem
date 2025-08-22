// Copyright  CtrlShiftSpace


#include "Player/TacticalCombatPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Input/TacticalCombatEnhInputComponent.h"
#include "Interaction/CameraInterface.h"

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
	TacticalCombatEnhInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ATacticalCombatPlayerController::Zoom);
}

void ATacticalCombatPlayerController::Zoom(const FInputActionValue& InputActionValue)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (ControlledPawn->Implements<UCameraInterface>())
		{
			const float ZoomValue = InputActionValue.Get<float>();
			if (ZoomValue == 0.f)
			{
				// 不進行縮放
				return;
			}
			if (ZoomValue > 0.f)
			{
				// 放大
				ICameraInterface::Execute_ZoomIn(ControlledPawn);
			}
			else
			{
				// 縮小
				ICameraInterface::Execute_ZoomOut(ControlledPawn);
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Zoom Value: %s"), *InputActionValue.ToString());
}
