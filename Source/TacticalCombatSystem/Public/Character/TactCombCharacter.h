// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Character/TactCombCharacterBase.h"
#include "Interaction/CameraInterface.h"
#include "Interaction/MovementInterface.h"
#include "TactCombCharacter.generated.h"

class ATactCombGridInstActor;
/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombCharacter : public ATactCombCharacterBase, public ICameraInterface, public IMovementInterface
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

protected:
	
	virtual void BeginPlay() override;

	/* Movement Interface */
	virtual void AssignMovement_Implementation(const FVector& MoveVector) override;
	virtual void AssignRotate_Implementation(const FRotator& Rotator) override;
	/** end Movement Interface */
	
	// 附屬於角色的網格
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid Class")
	TObjectPtr<UChildActorComponent> GridInstComponent;
	
};
