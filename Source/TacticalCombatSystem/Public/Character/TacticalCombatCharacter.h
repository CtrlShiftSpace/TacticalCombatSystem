// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Character/TacticalCombatCharacterBase.h"
#include "TacticalCombatCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATacticalCombatCharacter : public ATacticalCombatCharacterBase
{
	GENERATED_BODY()

public:
	/**
	 * 覆寫 PossessedBy 方法，當被 Controller 指派時會觸發
	 * 
	 * @param NewController 指派的 Controller
	 * @return 無回傳值
	 */
	virtual void PossessedBy(AController* NewController) override;
	
	
};
