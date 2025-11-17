// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Character/TactCombCharacterBase.h"
#include "Interaction/CameraInterface.h"
#include "Interaction/MovementInterface.h"
#include "Interaction/PlayerInterface.h"
#include "TactCombCharacter.generated.h"

class ATactCombPlayerState;
class ATactCombGridInstActor;
/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombCharacter : public ATactCombCharacterBase, public ICameraInterface, public IMovementInterface, public IPlayerInterface
{
	GENERATED_BODY()

public:
	ATactCombCharacter();
	
	/**
	 * 覆寫 PossessedBy 方法，當被 Controller 指派時會觸發
	 * 
	 * @param NewController 指派的 Controller
	 * @return 無回傳值
	 */
	virtual void PossessedBy(AController* NewController) override;

	/* Combat Interface */
	virtual int32 GetCharacterLevel_Implementation() override;
	/* end Combat Interface */

	/* Player Interface */
	virtual FPlayerAbilityInfo GetPlayerAbilityInfo_Implementation() const override;
	/* end Player Interface */
	
	
protected:
	
	virtual void BeginPlay() override;

	// 覆寫初始化 Ability
	virtual void InitAbilityActorInfo() override;

	/* Movement Interface */
	virtual void AssignMovement_Implementation(const FVector& MoveVector) override;
	virtual void AssignRotate_Implementation(const FRotator& Rotator) override;
	virtual void Jump_Implementation() override;
	/** end Movement Interface */

	// 取得 ATactCombPlayerState
	UFUNCTION(BlueprintPure)
	ATactCombPlayerState* GetTactCombPlayerState() const;

	// 是否為網格移動模式
	UPROPERTY(EditDefaultsOnly)
	bool bGridMoveMode = false;
	
	float MoveUnit = 200.f;
};
