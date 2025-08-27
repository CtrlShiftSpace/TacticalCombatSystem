// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "Interaction/CameraInterface.h"
#include "Interaction/MovementInterface.h"
#include "TacticalCombatMonitorPawn.generated.h"

class UTimelineComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TACTICALCOMBATSYSTEM_API ATacticalCombatMonitorPawn : public APawn, public ICameraInterface, public IMovementInterface
{
	GENERATED_BODY()

public:
	ATacticalCombatMonitorPawn();
	virtual void BeginPlay() override;
	
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

	/* Movement Interface */
	virtual void AssignMovement_Implementation(const FVector& MoveVector) override;
	/** end Movement Interface */

	UFUNCTION()
	void ZoomScaleChanged(const float InZoomScale);
	
protected:

	// 取得攝影機臂在不同倍率時的縮放長度
	UFUNCTION(BlueprintCallable)
	float GetScaleSpringArmLength(const float InZoomScale) const;

	UFUNCTION(BlueprintCallable)
	float GetZoomScale() const;

	UFUNCTION(BlueprintCallable)
	void SetZoomScale(const float InZoomScale);

	// 取得傳入倍率與目前倍率的差距
	UFUNCTION(BlueprintPure)
	float GetOffsetZoomScale(const float InZoomScale) const;
	
	// 攝影機臂用來調整攝影機位置和旋轉
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera Tools")
	TObjectPtr<USpringArmComponent> MonitorSpringArm;

	// 攝影機
	UPROPERTY(VisibleDefaultsOnly, Category = "Camera Tools")
	TObjectPtr<UCameraComponent> MonitorCamera;
	
	// 最大倍率
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Tools")
	float MaxZoomScale = 4.f;

	// 最小倍率
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Tools")
	float MinZoomScale = 0.5f;

	// 當前倍率
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Tools")
	float ZoomScale = 1.f;

	// 每次縮放的單位倍率
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Tools")
	float ZoomScaleUnit = 0.5f;

private:
	// 攝影機臂的預設長度
	float DefaultSpringArmLength;

	// Timeline 元件
	UPROPERTY()
	TObjectPtr<UTimelineComponent> TimelineComponent;

	// 控制攝影機縮放的曲線
	UPROPERTY(EditDefaultsOnly, Category = "Timeline Tools")
	TObjectPtr<UCurveFloat> MonitorCurve;

	// Timeline 更新縮放時的回呼函式
	FOnTimelineFloatStatic ZoomInterp;

	// Timeline 完成縮放時的回呼函式
	FOnTimelineEventStatic ZoomFinished;

	// 是否正在執行縮放
	bool bZooming = false;

	// 縮放前的倍率
	float BeforeZoomScale = 1.f;

	// 縮放前後的差距倍率
	float OffsetZoomScale = 0.f;

	// 移動速度
	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 10;
};
