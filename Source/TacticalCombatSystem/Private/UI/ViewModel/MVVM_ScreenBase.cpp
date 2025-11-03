// Copyright  CtrlShiftSpace


#include "UI/ViewModel/MVVM_ScreenBase.h"

void UMVVM_ScreenBase::SetViewModelScreenParams(const FViewModelScreenParams& VMParams)
{
	PlayerController = VMParams.PlayerController;
	PlayerState = VMParams.PlayerState;
	AbilitySystemComponent = VMParams.AbilitySystemComponent;
	AttributeSet = VMParams.AttributeSet;
}
