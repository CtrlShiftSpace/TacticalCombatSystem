// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MovementInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMovementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TACTICALCOMBATSYSTEM_API IMovementInterface
{
	GENERATED_BODY()

public:

	// 依照向量移動
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AssignMovement(const FVector& MoveVector);

	// 依照旋轉值旋轉
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AssignRotate(const FRotator& Rotator);
};
