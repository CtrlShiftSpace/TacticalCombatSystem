// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TactCombHUD.generated.h"

struct FWidgetControllerParams;
class UViewportWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
class UTactCombUserWidget;
/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombHUD : public AHUD
{
	GENERATED_BODY()

public:

	UViewportWidgetController* GetViewportWidgetController(const FWidgetControllerParams& WCParam);

	// 初始化 Viewport
	void InitViewport(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	
	// 用來指向 Viewport Widget 物件
	UPROPERTY()
	TObjectPtr<UTactCombUserWidget> ViewportWidget;

	// Viewport Widget 類別
	UPROPERTY(EditAnywhere, Category = "UI|Widget")
	TSubclassOf<UTactCombUserWidget> ViewportWidgetClass;

	// 用來指向 Viewport 控制器物件
	UPROPERTY()
	TObjectPtr<UViewportWidgetController> ViewportWidgetController;

	// Viewport 控制器類別
	UPROPERTY(EditAnywhere, Category = "UI|Widget Controller")
	TSubclassOf<UViewportWidgetController> ViewportWidgetControllerClass;
};
