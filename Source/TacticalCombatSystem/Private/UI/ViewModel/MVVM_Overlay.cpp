// Copyright  CtrlShiftSpace


#include "UI/ViewModel/MVVM_Overlay.h"

void UMVVM_Overlay::SetPlayerName(FString InPlayerName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, InPlayerName);
}

FString UMVVM_Overlay::GetPlayerName() const
{
	return PlayerName;
}
