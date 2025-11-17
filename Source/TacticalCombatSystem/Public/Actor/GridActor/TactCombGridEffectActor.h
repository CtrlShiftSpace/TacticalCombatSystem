// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "TactCombGridActor.h"
#include "TactCombGridEffectActor.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombGridEffectActor : public ATactCombGridActor
{
	GENERATED_BODY()

public:
	ATactCombGridEffectActor();
	
protected:
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
};
