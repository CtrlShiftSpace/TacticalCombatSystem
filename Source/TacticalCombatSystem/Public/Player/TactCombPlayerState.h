// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "TactCombPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
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
	UAttributeSet* GetAttributeSet() const;

	// 指派角色 ASC
	UAbilitySystemComponent* AssignAbilitySystemComponent(ACharacter& InPlayer);

	// 指派角色 AS
	UAttributeSet* AssignAttributeSet(ACharacter& InPlayer);
	
	// 取得目標角色的 ASC
	UAbilitySystemComponent* GetTargetAbilitySystemComponent(const ACharacter* InPlayer);

	// 取得目標角色的 ASC
	UAttributeSet* GetTargetAttributeSet(const ACharacter* InPlayer);
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	// 玩家控制角色的 ASC
	UPROPERTY(VisibleAnywhere)
	TMap<TObjectPtr<ACharacter>, TObjectPtr<UAbilitySystemComponent>> PlayerAbilitySystemComponents;

	// 玩家控制角色的 AS
	UPROPERTY()
	TMap<TObjectPtr<ACharacter>, UAttributeSet*> PlayerAttributeSets;

private:
	
	
};
