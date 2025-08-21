// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TacticalCombatInputConfig.generated.h"

class UInputAction;

// 指定 Input Action 與 Gameplay Tag 的對應關係
USTRUCT(BlueprintType)
struct FTacticalCombatInputMapping
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
	
};

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API UTacticalCombatInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
};
