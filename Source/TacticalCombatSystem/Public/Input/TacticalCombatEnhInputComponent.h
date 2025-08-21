// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "TacticalCombatInputConfig.h"
#include "TacticalCombatEnhInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API UTacticalCombatEnhInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:

	template<class UserClass, typename PressedFuncType, typename ReleaseedFuncType, typename HeldFuncType>
	void BindAbilityActions(const class UTacticalCombatInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleaseedFuncType ReleaseedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleaseedFuncType, typename HeldFuncType>
void UTacticalCombatEnhInputComponent::BindAbilityActions(const class UTacticalCombatInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleaseedFuncType ReleaseedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
}
