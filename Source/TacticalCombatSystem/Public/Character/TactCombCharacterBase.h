// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TactCombCharacterBase.generated.h"

UCLASS(Abstract)
class TACTICALCOMBATSYSTEM_API ATactCombCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATactCombCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
