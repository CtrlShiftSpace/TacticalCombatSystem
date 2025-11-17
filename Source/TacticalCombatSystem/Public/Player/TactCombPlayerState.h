// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "Interaction/PlayerInterface.h"
#include "TactCombPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

// 當玩家角色建立的 Delegate
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerCharacterSetup, const ACharacter* /* Player */)

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATactCombPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// 指派玩家的資訊
	FPlayerAbilityInfo AssignPlayerAbilityInfo(ACharacter& InPlayer);
	// 是否存在目標玩家的資訊
	bool HasTargetPlayerAbilityInfo(const ACharacter* InPlayer) const;
	// 取得目標玩家的資訊
	FPlayerAbilityInfo GetTargetPlayerAbilityInfo(const ACharacter* InPlayer) const;
	// 每當玩家角色建立呼叫
	void PlayerCharacterSetup(const ACharacter* Player);

	/* Delegate 定義 */
	FOnPlayerCharacterSetup OnPlayerCharacterSetup;

	/* end Delegate 定義 */

	
protected:
	
	// 玩家控制角色在遊戲中的資訊
	TMap<TObjectPtr<const ACharacter>, FPlayerAbilityInfo> PlayerAbilityInfoMap;
	
};
