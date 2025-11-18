// Copyright  CtrlShiftSpace


#include "UI/ViewModel/MVVM_Overlay.h"

void UMVVM_Overlay::SetPlayerName(FString InPlayerName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, InPlayerName);
}

void UMVVM_Overlay::SetCharacterLevel(int32 InCharacterLevel)
{
	UE_MVVM_SET_PROPERTY_VALUE(CharacterLevel, InCharacterLevel);
}

void UMVVM_Overlay::SetMaxHealth(int32 InMaxHealth)
{
	UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, InMaxHealth);
}

void UMVVM_Overlay::SetHealth(int32 InHealth)
{
	UE_MVVM_SET_PROPERTY_VALUE(Health, InHealth);
}

int32 UMVVM_Overlay::GetHealth() const
{
	return Health;
}

int32 UMVVM_Overlay::GetMaxHealth() const
{
	return MaxHealth;
}

int32 UMVVM_Overlay::GetCharacterLevel() const
{
	return CharacterLevel;
}

FString UMVVM_Overlay::GetPlayerName() const
{
	return PlayerName;
}
