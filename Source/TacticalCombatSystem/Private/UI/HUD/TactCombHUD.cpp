// Copyright  CtrlShiftSpace


#include "UI/HUD/TactCombHUD.h"

#include "UI/Widget/TactCombUserWidget.h"
#include "UI/WidgetController/ViewportWidgetController.h"

UViewportWidgetController* ATactCombHUD::GetViewportWidgetController(const FWidgetControllerParams& WCParam)
{
	if (ViewportWidgetController == nullptr)
	{
		// 如果不存在則創建一個新的 ViewportWidgetController
		ViewportWidgetController = NewObject<UViewportWidgetController>(this, ViewportWidgetControllerClass);
		ViewportWidgetController->SetWidgetControllerParams(WCParam);
	}
	return ViewportWidgetController;
}

void ATactCombHUD::InitViewport(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,
                                UAttributeSet* AS)
{
	// 檢查 ViewportWidgetClass 與 ViewportWidgetControllerClass 是否已經被設定
	checkf(ViewportWidgetClass, TEXT("Viewport Widget Class 尚未被設定，請在 BP_TactCombHUD 中設定"));
	checkf(ViewportWidgetControllerClass, TEXT("Viewport Widget Controller Class 尚未被設定，請在 BP_TactCombHUD 中設定"));

	// 建立 Viewport Widget 主要用於初始 UI 顯示
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), ViewportWidgetClass);
	ViewportWidget = Cast<UTactCombUserWidget>(Widget);

	// 建立 Viewport 的 Widget Controller
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UViewportWidgetController* WidgetController = GetViewportWidgetController(WidgetControllerParams);

	// 將 Viewport Widget Controller 設定為 Viewport Widget 的控制器
	ViewportWidget->SetWidgetController(WidgetController);

	// 將 Viewport Widget 加入到遊戲視窗中
	ViewportWidget->AddToViewport();
}
