// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
// 紀錄玩家 Ability 資訊
USTRUCT(BlueprintType)
struct FPlayerAbilityInfo
{
	GENERATED_BODY()

	// 玩家 ASC
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC = nullptr;

	// 玩家 AS
	UPROPERTY()
	TObjectPtr<UAttributeSet> AS = nullptr;

	// 玩家等級
	UPROPERTY()
	int32 PlayerLevel;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TACTICALCOMBATSYSTEM_API IPlayerInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FPlayerAbilityInfo GetPlayerAbilityInfo() const;
};
