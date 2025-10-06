// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Character/TactCombCharacterBase.h"
#include "Interaction/CameraInterface.h"
#include "TactCombCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombCharacter : public ATactCombCharacterBase, public ICameraInterface
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
