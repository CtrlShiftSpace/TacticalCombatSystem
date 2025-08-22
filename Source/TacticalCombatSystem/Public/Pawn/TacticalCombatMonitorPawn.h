// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interaction/CameraInterface.h"
#include "TacticalCombatMonitorPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TACTICALCOMBATSYSTEM_API ATacticalCombatMonitorPawn : public APawn, public ICameraInterface
{
	GENERATED_BODY()

public:
	ATacticalCombatMonitorPawn();

	/**
	 * 處理角色被接管時的事件
	 * 
	 * @param NewController 指派的 Controller
	 */
	virtual void PossessedBy(AController* NewController) override;

	/* Camera Interface */
	virtual void ZoomIn_Implementation() override;
	virtual void ZoomOut_Implementation() override;
	/** end Camera Interface */

protected:

	// 攝影機臂用來調整攝影機位置和旋轉
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera Tools")
	TObjectPtr<USpringArmComponent> MonitorSpringArm;

	// 攝影機
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera Tools")
	TObjectPtr<UCameraComponent> MonitorCamera;

	// 最大攝影機臂長度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Tools")
	float MaxTargetArmLength = 3000.f;

	// 最小攝影機臂長度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Tools")
	float MinTargetArmLength = 300.f;
	
	// 每次縮放的單位長度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Tools")
	float ZoomUnit = 500.f;
	
};
