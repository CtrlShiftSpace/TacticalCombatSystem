// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TactCombHUD.generated.h"

struct FViewModelScreenParams;
class UMVVM_Overlay;
class UMVVM_ScreenBase;
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

	// 取得 Overlay 畫面的 ViewModel
	UMVVM_Overlay* GetOverlayViewModel(const FViewModelScreenParams& VMParams);
	
	// 初始化 Viewport
	void InitViewport(APlayerController* PC, APlayerState* PS);

protected:
	/* MVVM 類別 */
	UPROPERTY(EditDefaultsOnly, Category = "UI|MVVM")
	TSubclassOf<UMVVM_ScreenBase> BasScrViewModelClass;

	/* end MVVM 類別 */

	/* MVVM 類別物件 */
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMVVM_ScreenBase> BasScrViewModel;

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

	// 畫面顯示UI的 ViewModel 類別
	UPROPERTY(EditDefaultsOnly, Category = "UI|ViewModels")
	TSubclassOf<UMVVM_Overlay> OverlayViewModelClass;

	// 畫面顯示UI的 ViewModel 物件
	UPROPERTY()
	TObjectPtr<UMVVM_Overlay> OverlayViewModel;
	
};
