// Copyright  CtrlShiftSpace


#include "Player/TactCombPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TactCombGameplayTags.h"
#include "Input/TactCombEnhInputComponent.h"
#include "Interaction/CameraInterface.h"
#include "Interaction/GridInterface.h"
#include "Interaction/MovementInterface.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Game/TactCombGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"


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

void ATactCombPlayerController::SwitchActor(AActor* NextActor)
{
	// 確保下一個控制對象有效
	if (!NextActor)
	{
		return;
	}

	if (APawn* NextPawn = Cast<APawn>(NextActor))
	{
		// 將原先的角色取消控制
		UnPossess();
		
		// 改為控制傳入的角色
		Possess(NextPawn);

		// 測試用，當玩家切換到角色控制時，顯示網格
		// if (ATactCombGameModeBase* TactCombGM = Cast<ATactCombGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		// {
		// 	const FTransform TransData(NextPawn->GetActorLocation());
		// 	TactCombGM->ShowGridInstActor(TransData);
		// }
	}
}

bool ATactCombPlayerController::IsSelectedGrid(const AActor* GridActor, const int32& Index) const
{
	for (const FSelectedGridInfo& Info : SelectedGrids)
	{
		if (Info.GridActor == GridActor && Info.GridIndex == Index)
		{
			return true;
		}
	}
	return false;
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

void ATactCombPlayerController::UnHightlightLastActor() const
{
	if (!LastActor)
	{
		return;
	}

	// 忽略已選取的網格
	if (IsSelectedGrid(LastActor, LastIndex))
	{
		return;
	}
	
	if (LastTraceActType == ETraceActType::Grid && LastIndex >= 0)
	{
		if (IGridInterface* GridInterface = Cast<IGridInterface>(LastActor))
		{
			GridInterface->UnHighlightByIndex(LastIndex);
		}
	}

	if (LastTraceActType == ETraceActType::Character)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UnHightlightLastActor Character"));
	}
}

void ATactCombPlayerController::HighlightThisActor() const
{
	if (!ThisActor)
	{
		return;
	}

	// 忽略已選取的網格
	if (IsSelectedGrid(ThisActor, ThisIndex))
	{
		return;
	}
	
	if (ThisTraceActType == ETraceActType::Grid && ThisIndex >= 0)
	{
		if (IGridInterface* GridInterface = Cast<IGridInterface>(ThisActor))
		{
			GridInterface->HighlightByIndex(ThisIndex);
		}
	}

	if (ThisTraceActType == ETraceActType::Character)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HightlightLastActor Character"));
	}
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
	const FTactCombGameplayTags TactCombGameplayTags = FTactCombGameplayTags::Get();

	if (ThisActor != nullptr && InputTag.MatchesTagExact(TactCombGameplayTags.InputTag_Grid_Interact))
	{
		// 先取消所有選取資料
		for (const FSelectedGridInfo& Info : SelectedGrids)
		{
			if (IGridInterface* GridInterface = Cast<IGridInterface>(Info.GridActor))
			{
				GridInterface->DeselectedByIndex(Info.GridIndex);
			}
		}
		// 清空已選取陣列
		SelectedGrids.Empty();
		// 建立已選取網格資料
		FSelectedGridInfo Info;
		Info.GridActor = ThisActor;
		Info.GridIndex = ThisIndex;
		// 加入已選取陣列中
		SelectedGrids.Add(Info);

		// 確認角色是否實作了 CombatInterface
		if (ThisActor->Implements<UCombatInterface>())
		{
			// 切換角色
			SwitchActor(ThisActor);
		}else if (IGridInterface* GridInterface = Cast<IGridInterface>(ThisActor))
		{
			GridInterface->SelectedByIndex(ThisIndex);
		}
		return;
	}

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// 確認角色是否實作了 MovementInterface
		if (ControlledPawn->Implements<UMovementInterface>())
		{
			if (InputTag.MatchesTagExact(TactCombGameplayTags.InputTag_Action_Jump))
			{
				IMovementInterface::Execute_Jump(ControlledPawn);
			}
		}
		
		// 確認角色是否實作了 CameraInterface
		if (ControlledPawn->Implements<UCameraInterface>())
		{
			// 根據輸入標籤來決定是放大還是縮小
			if (InputTag.MatchesTagExact(TactCombGameplayTags.InputTag_Zoom_In))
			{
				// 放大
				ICameraInterface::Execute_ZoomIn(ControlledPawn);
			}
			else
			{
				if (InputTag.MatchesTagExact(TactCombGameplayTags.InputTag_Zoom_Out))
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
	
	// 紀錄上次的追蹤到的物件
	LastActor = ThisActor;
	LastTraceActType = ThisTraceActType;
	LastIndex = ThisIndex;

	if (!TraceMouseHit.bBlockingHit)
	{
		// 如果未有偵測到任何物件，則清空目前追蹤狀態
		ThisTraceActType = ETraceActType::None;
		ThisActor = nullptr;
		ThisIndex = INDEX_NONE;

		// 取消上次的標記
		UnHightlightLastActor();
		return;
	}
	
	if (TraceMouseHit.GetActor()->Implements<UGridInterface>())
	{
		// 偵測到網格
		ThisTraceActType = ETraceActType::Grid;
		ThisActor = TraceMouseHit.GetActor();
		// 該物件含有 InstancedStaticMeshComponent
		if (TraceMouseHit.Component->IsA(UInstancedStaticMeshComponent::StaticClass()))
		{
			ThisIndex = TraceMouseHit.Item;
			// 取得 Pivot 位置
			// const FVector PivotLoc = IGridInterface::Execute_GetPivotByIndex(TraceMouseHit.GetActor(), ThisInstanceIndex);
		}
		else
		{
			ThisIndex = INDEX_NONE;
		}

		// 如果上次追蹤到的物件與這次不同，取消上次的標記
		if (LastTraceActType != ThisTraceActType)
		{
			UnHightlightLastActor();
			HighlightThisActor();
		}
		else
		{
			if (ThisActor != LastActor || LastIndex != ThisIndex)
			{
				UnHightlightLastActor();
				HighlightThisActor();
			}
		}
	}
	else if (TraceMouseHit.GetActor()->Implements<UCombatInterface>())
	{
		// 偵測到角色
		ThisActor = TraceMouseHit.GetActor();
		ThisTraceActType = ETraceActType::Character;
		ThisIndex = INDEX_NONE;
		if (LastTraceActType != ThisTraceActType || ThisActor != LastActor)
		{
			UnHightlightLastActor();
			HighlightThisActor();
		}
	}
	else
	{
		ThisActor = nullptr;
		ThisIndex = INDEX_NONE;
		UnHightlightLastActor();
	}
}
