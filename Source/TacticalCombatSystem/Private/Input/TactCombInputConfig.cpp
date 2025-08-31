// Copyright  CtrlShiftSpace


#include "Input/TactCombInputConfig.h"

const UInputAction* UTactCombInputConfig::FindInputActionForTag(const FGameplayTag& InputTag, const bool bLogNotFound /*= false*/) const
{
	for (FTacticalCombatInputMapping InputMapping : AbilityInputMappings)
	{
		if (InputMapping.InputTag == InputTag)
		{
			return InputMapping.InputAction;
		}
	}
	if (bLogNotFound)
	{
		// 未找到符合該 Input Tag 定義的 Input Action，則輸出警告訊息
		UE_LOG(LogTemp, Warning, TEXT("UTactCombInputConfig::FindInputActionForTag: Cannot find InputAction for Tag %s"), *InputTag.ToString());
	}
	return nullptr;
}
