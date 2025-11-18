// Copyright  CtrlShiftSpace


#include "UI/ViewModel/MVVM_ScreenBase.h"

#include "AbilitySystem/TactCombAttributeSet.h"
#include "GameFramework/Character.h"
#include "Player/TactCombPlayerState.h"

void UMVVM_ScreenBase::SetViewModelScreenParams(const FViewModelScreenParams& VMParams)
{
	PlayerController = VMParams.PlayerController;
	PlayerState = VMParams.PlayerState;
}
