// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "TactCombInputConfig.h"
#include "TactCombEnhInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API UTactCombEnhInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template <class SourceClass, typename PressedKeyFuncType, typename ReleasedKeyFuncType, typename HeldKeyFuncType>
	void BindAbilityActions(UTactCombInputConfig* InputConfig, SourceClass* Object, PressedKeyFuncType PressedFunc, ReleasedKeyFuncType ReleasedFunc, HeldKeyFuncType HeldFunc);
};

template <class SourceClass, typename PressedKeyFuncType, typename ReleasedKeyFuncType, typename HeldKeyFuncType>
void UTactCombEnhInputComponent::BindAbilityActions(UTactCombInputConfig* InputConfig, SourceClass* Object, PressedKeyFuncType PressedFunc, ReleasedKeyFuncType ReleasedFunc, HeldKeyFuncType HeldFunc)
{
	check(InputConfig);
	
	for (const FTacticalCombatInputMapping Mapping : InputConfig->AbilityInputMappings)
	{
		if (Mapping.InputAction && Mapping.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Mapping.InputAction, ETriggerEvent::Started, Object, PressedFunc, Mapping.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Mapping.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Mapping.InputTag);
			}
		
			if (HeldFunc)
			{
				BindAction(Mapping.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Mapping.InputTag);
			}
		}
	}
}
