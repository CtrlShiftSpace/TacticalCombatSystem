// Copyright  CtrlShiftSpace


#include "Player/TactCombPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/TactCombAbilitySystemComponent.h"
#include "AbilitySystem/TactCombAttributeSet.h"
#include "GameFramework/Character.h"

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

UAbilitySystemComponent* ATactCombPlayerState::AssignAbilitySystemComponent(ACharacter& InPlayer)
{
	const FString ASCName = FString::Printf(TEXT("%s_ASC"), *InPlayer.GetName());
	// 建立 ASC
	UTactCombAbilitySystemComponent* TactCombASC = NewObject<UTactCombAbilitySystemComponent>(this, FName(*ASCName));
	// 動態創建需要 Register
	TactCombASC->RegisterComponent();
	// 設定一致server 與 client的狀態會同步
	TactCombASC->SetIsReplicated(true);
	TactCombASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	// 設定 Owner 為 Player Stat，Avatar 為傳入的 Character
	TactCombASC->InitAbilityActorInfo(this, &InPlayer);
	// 加入 TMap 中並回傳此次建立的物件
	PlayerAbilitySystemComponents.Add(&InPlayer, TactCombASC);
	return TactCombASC;
}

UAttributeSet* ATactCombPlayerState::AssignAttributeSet(ACharacter& InPlayer)
{
	const FString ASName = FString::Printf(TEXT("%s_AS"), *InPlayer.GetName());
	// 建立 AS
	UTactCombAttributeSet* TactCombAS = NewObject<UTactCombAttributeSet>(this, FName(*ASName));
	// 加入 TMap 中並回傳此次建立的物件
	PlayerAttributeSets.Add(&InPlayer, TactCombAS);
	return TactCombAS;
}

UAbilitySystemComponent* ATactCombPlayerState::GetTargetAbilitySystemComponent(const ACharacter* InPlayer)
{
	if (InPlayer == nullptr || !PlayerAbilitySystemComponents.Contains(InPlayer))
	{
		return nullptr;
	}
	return PlayerAbilitySystemComponents[InPlayer];
}

UAttributeSet* ATactCombPlayerState::GetTargetAttributeSet(const ACharacter* InPlayer)
{
	if (InPlayer == nullptr || !PlayerAttributeSets.Contains(InPlayer))
	{
		return nullptr;
	}
	return PlayerAttributeSets[InPlayer];
}
