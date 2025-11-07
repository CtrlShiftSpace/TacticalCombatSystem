// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TactCombUserWidget.generated.h"

class UMVVM_ScreenBase;
/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API UTactCombUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	// 用來設定此 Widget 由哪個 Widget Controller 控制
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetContoller);

	// 用來設定此 Widget 由哪個 ViewModel 管理
	UFUNCTION(BlueprintCallable)
	void SetWidgetVM(UMVVM_ScreenBase* InViewModel);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	// 此 Widget 對應的 View Model
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMVVM_ScreenBase> WidgetVM;

protected:
	// 一旦設定好 Widget Controller 後會呼叫此函式，在 Widget Blueprint 實作細節
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

	// 一旦設定好 Widget View Model 後會呼叫此函式，在 Widget Blueprint 實作細節
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetVMSet();
	
};
