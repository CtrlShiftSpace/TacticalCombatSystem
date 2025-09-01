// Copyright  CtrlShiftSpace


#include "Player/TactCombPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/TactCombAbilitySystemComponent.h"
#include "AbilitySystem/TactCombAttributeSet.h"

ATactCombPlayerState::ATactCombPlayerState()
{
	// 主要用於控制對象(遊戲角色、物體)狀態的更新頻率
	NetUpdateFrequency = 100.f;
	
	AbilitySystemComponent = CreateDefaultSubobject<UTactCombAbilitySystemComponent>("AbilitySystemComponent");
	// 設定一致server 與 client的狀態會同步
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UTactCombAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ATactCombPlayerState::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
}

UAttributeSet* ATactCombPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
