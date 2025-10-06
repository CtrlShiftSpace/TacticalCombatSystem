// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CameraInterface.generated.h"

// 進行縮放事件的委託
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZoomScaleChangedSignature, const float, NewTargetArmLength);

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

	// 切換攝影機
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SwitchCamera(AActor* NextViewer);
	
};
