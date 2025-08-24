// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TacticalCombatPlayerController.generated.h"

struct FGameplayTag;
class UTacticalCombatInputConfig;
class ATacticalCombatMonitorPawn;
class UInputMappingContext;

struct FInputActionValue;
class UInputAction;

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATacticalCombatPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// 建構式
	ATacticalCombatPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:

	// 放大縮小行為的處理函式
	void Zoom(const FInputActionValue& InputActionValue);
	
	// 處理輸入Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TObjectPtr<UInputMappingContext> TactCombContext;

	// 放大縮小行為
	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TObjectPtr<UInputAction> ZoomAction;
	
	// 輸入設定
	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TObjectPtr<UTacticalCombatInputConfig> InputConfig;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
};
