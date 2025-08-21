// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TacticalCombatPlayerController.generated.h"

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
	void Zoom(const FInputActionValue& Value);
	
	// 處理輸入Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TObjectPtr<UInputMappingContext> TactCombContext;

	// 放大縮小行為
	UPROPERTY(EditDefaultsOnly, Category = "Input Settings")
	TObjectPtr<UInputAction> ZoomAction;
};
