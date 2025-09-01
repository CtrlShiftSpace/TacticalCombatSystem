// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TactCombUserWidget.generated.h"

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

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	// 一旦設定好 Widget Controller 後會呼叫此函式，在 Widget Blueprint 實作細節
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
