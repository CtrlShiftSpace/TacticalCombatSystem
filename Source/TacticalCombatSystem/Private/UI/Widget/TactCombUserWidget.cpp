// Copyright  CtrlShiftSpace


#include "UI/Widget/TactCombUserWidget.h"

void UTactCombUserWidget::SetWidgetController(UObject* InWidgetContoller)
{
	WidgetController = InWidgetContoller;
	WidgetControllerSet();
}
