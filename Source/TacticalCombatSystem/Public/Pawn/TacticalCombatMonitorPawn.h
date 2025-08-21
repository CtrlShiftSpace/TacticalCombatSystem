// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TacticalCombatMonitorPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TACTICALCOMBATSYSTEM_API ATacticalCombatMonitorPawn : public APawn
{
	GENERATED_BODY()

public:
	ATacticalCombatMonitorPawn();

protected:

	// 攝影機臂用來調整攝影機位置和旋轉
	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	TObjectPtr<USpringArmComponent> MonitorSpringArm;

	// 攝影機
	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	TObjectPtr<UCameraComponent> MonitorCamera;
};
