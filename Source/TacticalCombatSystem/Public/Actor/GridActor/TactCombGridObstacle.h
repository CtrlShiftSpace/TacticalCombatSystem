// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Actor/GridActor/TactCombGridActor.h"
#include "TactCombGridObstacle.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombGridObstacle : public ATactCombGridActor
{
	GENERATED_BODY()
	
public:
	ATactCombGridObstacle();

	UFUNCTION(BlueprintCallable)
	void UpdateGridShape(const UGridClassInfo* GridClassInfo);
};
