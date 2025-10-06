// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "TactCombCharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS(Abstract)
class TACTICALCOMBATSYSTEM_API ATactCombCharacterBase : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATactCombCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 追蹤角色攝影彈簧臂
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CharSprArm;

	// 追蹤角色攝影機
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> CharCam;
};
