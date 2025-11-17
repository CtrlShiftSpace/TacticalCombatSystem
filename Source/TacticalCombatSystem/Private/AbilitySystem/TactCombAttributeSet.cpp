// Copyright  CtrlShiftSpace


#include "AbilitySystem/TactCombAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TactCombGameplayTags.h"
#include "Net/UnrealNetwork.h"

UTactCombAttributeSet::UTactCombAttributeSet()
{
	const FTactCombGameplayTags& GameplayTags = FTactCombGameplayTags::Get();
}

void UTactCombAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 以下註冊 UTactCombAttributeSet 類別中的變數值，將其同步到 Client ，並會觸發對應的 OnRep 函式

	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UTactCombAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTactCombAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTactCombAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
}

void UTactCombAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UTactCombAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTactCombAttributeSet, Health, OldHealth);
}

void UTactCombAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTactCombAttributeSet, MaxHealth, OldMaxHealth);
}

void UTactCombAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTactCombAttributeSet, Vigor, OldVigor);
}
