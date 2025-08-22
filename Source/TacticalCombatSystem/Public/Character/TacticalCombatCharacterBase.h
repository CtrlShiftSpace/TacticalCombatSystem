// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TacticalCombatCharacterBase.generated.h"

UCLASS(Abstract)
class TACTICALCOMBATSYSTEM_API ATacticalCombatCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATacticalCombatCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
