// Copyright  CtrlShiftSpace


#include "Player/TactCombPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TactCombGameplayTags.h"
#include "Input/TactCombEnhInputComponent.h"
#include "Interaction/CameraInterface.h"
#include "Interaction/GridInterface.h"
#include "Interaction/MovementInterface.h"
#include "TacticalCombatSystem/TacticalCombatSystem.h"
#include "Components/InstancedStaticMeshComponent.h"

ATactCombPlayerController::ATactCombPlayerController()
{
	bReplicates = true;
}

void ATactCombPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	// 每一幀都檢測滑鼠游標位置
	TraceMouse();
}

void ATactCombPlayerController::BeginPlay()
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

void ATactCombPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UTactCombEnhInputComponent* TacticalCombatEnhInputComponent = CastChecked<UTactCombEnhInputComponent>(InputComponent);
	// 綁定輸入移動行為
	TacticalCombatEnhInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	TacticalCombatEnhInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ThisClass::Rotate);
	TacticalCombatEnhInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ATactCombPlayerController::Move(const FInputActionValue& InputActionValue)
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

void ATactCombPlayerController::Rotate(const FInputActionValue& InputActionValue)
{
	const FVector RotatorVector = InputActionValue.Get<FVector>();
	const float YawRate = RotatorVector.X;
	// 旋轉角度
	const FRotator Rotator = FRotator(0.f, RotatorYawAngle * YawRate, 0.f);
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (ControlledPawn->Implements<UMovementInterface>())
		{
			IMovementInterface::Execute_AssignRotate(ControlledPawn, Rotator);
		}
	}
}

void ATactCombPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// 確認角色是否實作了 CameraInterface
		if (ControlledPawn->Implements<UCameraInterface>())
		{
			// 根據輸入標籤來決定是放大還是縮小
			if (InputTag.MatchesTagExact(FTactCombGameplayTags::Get().InputTag_Zoom_In))
			{
				// 放大
				ICameraInterface::Execute_ZoomIn(ControlledPawn);
			}
			else
			{
				if (InputTag.MatchesTagExact(FTactCombGameplayTags::Get().InputTag_Zoom_Out))
				{
					// 縮小
					ICameraInterface::Execute_ZoomOut(ControlledPawn);
				}
			}
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("AbilityInputTagPressed: %s"), *InputTag.ToString());
}

void ATactCombPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
}

void ATactCombPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
}

void ATactCombPlayerController::TraceMouse()
{
	// 取得滑鼠游標在畫面中檢測到的結果
	GetHitResultUnderCursor(ECC_Visibility, false, TraceMouseHit);
	
	// 紀錄上次的追蹤到的網格物件
	LastGridActor = ThisGridActor;
	LastInstanceIndex = ThisInstanceIndex;
	// 目前追蹤到的網格物件
	if (TraceMouseHit.bBlockingHit && TraceMouseHit.GetActor()->Implements<UGridInterface>())
	{
		ThisGridActor = TraceMouseHit.GetActor();
		// 該物件含有 InstancedStaticMeshComponent
		if (TraceMouseHit.Component->IsA(UInstancedStaticMeshComponent::StaticClass()))
		{
			ThisInstanceIndex = TraceMouseHit.Item;
			// 取得 Pivot 位置
			// const FVector PivotLoc = IGridInterface::Execute_GetPivotByIndex(TraceMouseHit.GetActor(), ThisInstanceIndex);
		}
		else
		{
			ThisInstanceIndex = INDEX_NONE;
		}
	}
	else
	{
		ThisGridActor = nullptr;
		ThisInstanceIndex = INDEX_NONE;
	}

	// 如果上次追蹤到的物件與這次不同，才進行高亮與取消高亮
	if (LastGridActor != ThisGridActor || LastInstanceIndex != ThisInstanceIndex)
	{
		if (LastGridActor)
		{
			LastGridActor->UnHighlightByIndex(LastInstanceIndex);
		}
		if (ThisGridActor)
		{
			ThisGridActor->HighlightByIndex(ThisInstanceIndex);
		}
	}
}
