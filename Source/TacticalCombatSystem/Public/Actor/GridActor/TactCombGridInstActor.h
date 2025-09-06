// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Actor/GridActor/TactCombGridActorBase.h"
#include "TactCombGridInstActor.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombGridInstActor : public ATactCombGridActorBase
{
	GENERATED_BODY()
	
public:
	ATactCombGridInstActor();
	
protected:
	virtual void BeginPlay() override;

	// 靜態 Instance 物件
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInstancedStaticMeshComponent> GridInstMesh;
	
};
