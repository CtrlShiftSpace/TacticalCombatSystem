// Copyright  CtrlShiftSpace


#include "Player/TactCombPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/TactCombAbilitySystemComponent.h"
#include "AbilitySystem/TactCombAttributeSet.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"

ATactCombPlayerState::ATactCombPlayerState()
{
	// 主要用於控制對象(遊戲角色、物體)狀態的更新頻率
	NetUpdateFrequency = 100.f;
	// 綁定一旦玩家角色建立時所執行的事件
	OnPlayerCharacterSetup.AddUObject(this, &ThisClass::PlayerCharacterSetup);
	
}

UAbilitySystemComponent* ATactCombPlayerState::GetAbilitySystemComponent() const
{
	if (const APlayerController* PC = GetPlayerController())
	{
		// 檢查目前 Player Controller 控制的 Pawn 是否為 Character
		if (const ACharacter* PlayerCharacter = Cast<ACharacter>(PC->GetPawn()))
		{
			// 回傳當前控制的 Character 的 ASC
			return GetTargetPlayerAbilityInfo(PlayerCharacter).ASC;
		}
	}
	return nullptr;
}

FPlayerAbilityInfo ATactCombPlayerState::AssignPlayerAbilityInfo(ACharacter& InPlayer)
{
	FPlayerAbilityInfo PlayerAbilityInfo;
	// const FString ASCName = FString::Printf(TEXT("%s_ASC"), *InPlayer.GetName());
	// 建立 ASC
	UTactCombAbilitySystemComponent* TactCombASC = NewObject<UTactCombAbilitySystemComponent>(this, UTactCombAbilitySystemComponent::StaticClass());
	// 動態創建需要 Register
	TactCombASC->RegisterComponent();
	// 設定一致server 與 client的狀態會同步
	TactCombASC->SetIsReplicated(true);
	TactCombASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	// 設定 Owner 為 Player Stat，Avatar 為傳入的 Character
	TactCombASC->InitAbilityActorInfo(this, &InPlayer);
	
	// const FString ASName = FString::Printf(TEXT("%s_AS"), *InPlayer.GetName());
	// 建立 AS
	UTactCombAttributeSet* TactCombAS = NewObject<UTactCombAttributeSet>(this, UTactCombAttributeSet::StaticClass());
	
	PlayerAbilityInfo.ASC = TactCombASC;
	PlayerAbilityInfo.AS = TactCombAS;
	// 角色等級
	if (InPlayer.Implements<UCombatInterface>())
	{
		PlayerAbilityInfo.PlayerLevel = ICombatInterface::Execute_GetCharacterLevel(&InPlayer);
	}
	PlayerAbilityInfoMap.Add(&InPlayer, PlayerAbilityInfo);

	return PlayerAbilityInfo;
}

bool ATactCombPlayerState::HasTargetPlayerAbilityInfo(const ACharacter* InPlayer) const
{
	if (InPlayer != nullptr && PlayerAbilityInfoMap.Contains(InPlayer))
	{
		return true;
	}
	return false;
}

FPlayerAbilityInfo ATactCombPlayerState::GetTargetPlayerAbilityInfo(const ACharacter* InPlayer) const
{
	return HasTargetPlayerAbilityInfo(InPlayer) ? PlayerAbilityInfoMap[InPlayer] : FPlayerAbilityInfo();
}

void ATactCombPlayerState::PlayerCharacterSetup(const ACharacter* Player)
{
	// 確認是否實作 PlayerInterface
	if (!Player->Implements<UPlayerInterface>())
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacterSetup: Player %s does not implement UPlayerInterface."), *Player->GetName());
		return;
	}

	// 將玩家資訊放入陣列中
	const FPlayerAbilityInfo PlayerAbilityInfo = IPlayerInterface::Execute_GetPlayerAbilityInfo(Player);
	PlayerAbilityInfoMap.Add(Player, PlayerAbilityInfo);
	
}
