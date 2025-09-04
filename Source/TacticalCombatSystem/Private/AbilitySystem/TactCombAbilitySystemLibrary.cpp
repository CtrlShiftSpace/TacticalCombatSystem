// Copyright  CtrlShiftSpace


#include "AbilitySystem/TactCombAbilitySystemLibrary.h"
#include "Game/TactCombGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UGridClassInfo* UTactCombAbilitySystemLibrary::GetGridClassInfo(const UObject* WorldContextObject)
{
	// 取得GameMode
	const ATactCombGameModeBase* TactCombGameMode = Cast<ATactCombGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (TactCombGameMode == nullptr) { return nullptr; }
	return TactCombGameMode->GridClassInfo;
}
