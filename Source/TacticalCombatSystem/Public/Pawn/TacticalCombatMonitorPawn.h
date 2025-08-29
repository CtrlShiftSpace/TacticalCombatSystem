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

// 用來建立 Float Timeline 曲線與事件結構
struct FTactCombFloatTimelineEvent
{
	// Timeline 線段與執行Delegate
	UCurveFloat* Curve;

	FOnTimelineFloatStatic InterpDelegate;

	// Timeline 結束 Delegate
	FOnTimelineEventStatic FinishedDelegate;
};

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
	virtual void AssignRotate_Implementation(const FRotator& Rotator) override;
	/** end Movement Interface */

	UFUNCTION()
	void ZoomScaleChanged(const float InZoomScale);

	UFUNCTION()
	void LocationChanged(const FVector& InLocation);

	UFUNCTION()
	void RotatorChanged(const FRotator& InRotator);

	// 建立 Float Timeline 元件的工具函式
	void AssignTactCombFloatTimelineComponent(UTimelineComponent& TactCombTimelineComponent, const FTactCombFloatTimelineEvent& TactCombFloatTimelineEvent);
	
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

	// 取得攝影機在不同 Yaw 時的旋轉
	UFUNCTION(BlueprintPure)
	float GetOffsetYaw(const float InYaw) const;
	
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

	// 攝影機的預設旋轉
	FRotator DefaultMonitorRotator;

	// 縮放 Timeline 元件
	UPROPERTY()
	TObjectPtr<UTimelineComponent> ZoomTimelineComponent;

	// 旋轉 Timeline 元件
	UPROPERTY()
	TObjectPtr<UTimelineComponent> RotateTimelineComponent;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> MoveTimelineComponent;
	
	// 控制攝影機縮放的曲線
	UPROPERTY(EditDefaultsOnly, Category = "Timeline Tools")
	TObjectPtr<UCurveFloat> MonitorZoomCurve;

	// 控制攝影機移動的曲線
	UPROPERTY(EditDefaultsOnly, Category = "Timeline Tools")
	TObjectPtr<UCurveFloat> MonitorMoveCurve;

	// 控制攝影機旋轉的曲線
	UPROPERTY(EditDefaultsOnly, Category = "Timeline Tools")
	TObjectPtr<UCurveFloat> MonitorRotateCurve;

	/**
	 * Timeline 更新縮放時的事件
	 * 
	 * @param InterpValue 插值
	 */
	UFUNCTION()
	void ZoomInterpEvent(const float InterpValue);

	/**
	 * Timeline 更新完成縮放的事件
	 */
	UFUNCTION()
	void ZoomFinishedEvent();


	/**
	 * Timeline 更新移動時的事件
	 * 
	 * @param InterpValue 插值
	 */
	UFUNCTION()
	void MoveInterpEvent(const float InterpValue);

	/**
	 * Timeline 更新完成移動的事件
	 */
	UFUNCTION()
	void MoveFinishedEvent();
	
	/**
	 * Timeline 更新旋轉轉動時的事件
	 * 
	 * @param InterpValue 
	 */
	UFUNCTION()
	void RotateYawInterpEvent(const float InterpValue);

	/**
	 * Timeline 更新完成旋轉的事件
	 */
	UFUNCTION()
	void RotateFinishedEvent();
	
	bool bZooming = false;
	bool bMoving = false;
	bool bRotating = false;

	// 縮放前的倍率
	float BeforeZoomScale = 1.f;

	// 縮放前後的差距倍率
	float OffsetZoomScale = 0.f;

	// 移動速度
	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed = 300.f;

	// 移動前的位置
	FVector BeforeLocation;

	// 移動前後的差距位置
	FVector OffsetLocation;

	// 旋轉前的 Yaw
	float BeforeYaw;

	// 旋轉前後的差距 Yaw
	float OffsetYaw;
};
