// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TactCombPlayerController.generated.h"

class IGridInterface;
struct FGameplayTag;
class UTactCombInputConfig;
class ATactCombMonitorPawn;
class UInputMappingContext;

struct FInputActionValue;
class UInputAction;

// 追蹤物件類型
UENUM()
enum ETraceActType : uint8
{
	None,
	Grid,
	Character
};

// 已選取的網格資訊
USTRUCT()
struct FSelectedGridInfo
{
	GENERATED_BODY()

	// 網格物件
	UPROPERTY()
	AActor* GridActor = nullptr;

	// 網格索引
	UPROPERTY()
	int32 GridIndex = INDEX_NONE;
};

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// 建構式
	ATactCombPlayerController();
	virtual void PlayerTick(float DeltaTime);

	// 切換下一個控制對象
	void SwitchActor(AActor* NextActor);

	// 檢查網格是否已被選取
	bool IsSelectedGrid(const TScriptInterface<IGridInterface>& GridInterface, const int32& Index) const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// 標記與取消標記
	void UnHightlightLastActor() const;
	void HighlightThisActor() const;
	
private:
	
	// 處理輸入Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TObjectPtr<UInputMappingContext> TactCombContext;

	// 放大縮小行為
	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TObjectPtr<UInputAction> ZoomAction;
	
	// 輸入設定
	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TObjectPtr<UTactCombInputConfig> InputConfig;

	// 處理移動的 Input Action
	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TObjectPtr<UInputAction> MoveAction;

	// 處理旋轉的 Input Action
	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TObjectPtr<UInputAction> RotateAction;
	
	// 移動
	void Move(const FInputActionValue& InputActionValue);

	// 旋轉
	void Rotate(const FInputActionValue& InputActionValue);
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	// 旋轉角度
	float RotatorYawAngle = 45.f;

	// 追蹤滑鼠資訊
	void TraceMouse();

	// 追蹤所偵測的物件
	FHitResult TraceMouseHit;

	// 上次與當前偵測到的物件
	TScriptInterface<IGridInterface> LastActor;
	TScriptInterface<IGridInterface> ThisActor;

	ETraceActType LastTraceActType = ETraceActType::None;
	ETraceActType ThisTraceActType = ETraceActType::None;

	// 上次與當前偵測到的索引
	int32 LastIndex = INDEX_NONE;
	int32 ThisIndex = INDEX_NONE;

	// 已選取的網格
	TArray<FSelectedGridInfo> SelectedGrids;
};
