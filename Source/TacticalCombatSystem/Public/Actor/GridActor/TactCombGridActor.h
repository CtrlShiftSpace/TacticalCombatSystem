// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Actor/GridActor/TactCombGridActorBase.h"
#include "TactCombGridActor.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombGridActor : public ATactCombGridActorBase
{
	GENERATED_BODY()

public:
	ATactCombGridActor();
	
	
protected:
	virtual void BeginPlay() override;
	
	// 靜態物件
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> GridMesh;
	
};
