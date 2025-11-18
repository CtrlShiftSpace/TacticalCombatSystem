// Copyright  CtrlShiftSpace


#include "UI/HUD/TactCombHUD.h"

#include "UI/ViewModel/MVVM_Overlay.h"
#include "UI/ViewModel/MVVM_ScreenBase.h"
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

UMVVM_Overlay* ATactCombHUD::GetOverlayViewModel(const FViewModelScreenParams& VMParams)
{
	// 確認 OverlayViewModelClass 為已設定狀態
	check(OverlayViewModelClass);

	if (OverlayViewModel == nullptr)
	{
		// 如果不存在則創建一個新的 OverlayViewModel
		OverlayViewModel = NewObject<UMVVM_Overlay>(this, OverlayViewModelClass);
		OverlayViewModel->SetViewModelScreenParams(VMParams);
	}
	return OverlayViewModel;
}

void ATactCombHUD::InitViewport(APlayerController* PC, APlayerState* PS)
{
	// 檢查 ViewportWidgetClass 與 ViewportWidgetControllerClass 是否已經被設定
	checkf(ViewportWidgetClass, TEXT("Viewport Widget Class 尚未被設定，請在 BP_TactCombHUD 中設定"));
	checkf(ViewportWidgetControllerClass, TEXT("Viewport Widget Controller Class 尚未被設定，請在 BP_TactCombHUD 中設定"));

	// 建立 Viewport Widget 主要用於初始 UI 顯示
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), ViewportWidgetClass);
	ViewportWidget = Cast<UTactCombUserWidget>(Widget);

	// 建立 Viewport 的 View Model
	const FViewModelScreenParams ViewModelScreenParams(PC, PS);
	UMVVM_Overlay* ViewModel = GetOverlayViewModel(ViewModelScreenParams);

	// 設定 View Model
	ViewportWidget->SetWidgetVM(ViewModel);
	
	// 將 Viewport Widget 加入到遊戲視窗中
	ViewportWidget->AddToViewport();
}
