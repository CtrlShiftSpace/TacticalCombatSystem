// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TactCombPlayerController.generated.h"

struct FGameplayTag;
class UTactCombInputConfig;
class ATactCombMonitorPawn;
class UInputMappingContext;

struct FInputActionValue;
class UInputAction;

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

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
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
	
	
};
