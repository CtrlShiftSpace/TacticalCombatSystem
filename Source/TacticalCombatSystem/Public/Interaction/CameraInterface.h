// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CameraInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCameraInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TACTICALCOMBATSYSTEM_API ICameraInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ZoomIn();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ZoomOut();

	
};
