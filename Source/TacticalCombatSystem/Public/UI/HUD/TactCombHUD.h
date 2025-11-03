// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TactCombHUD.generated.h"

class UMVVM_BasicScreen;
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

protected:
	/* MVVM 類別 */
	UPROPERTY(EditDefaultsOnly, Category = "UI|MVVM")
	TSubclassOf<UMVVM_BasicScreen> BasScrViewModelClass;

	/* end MVVM 類別 */

	/* MVVM 類別物件 */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMVVM_BasicScreen> BasScrViewModel;

	/* end MVVM 類別物件 */
	
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
