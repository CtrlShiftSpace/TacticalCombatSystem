// Copyright  CtrlShiftSpace


#include "AbilitySystem/Data/CharacterClassInfoBase.h"

FCharacterClassDefaultInfo UCharacterClassInfoBase::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}
