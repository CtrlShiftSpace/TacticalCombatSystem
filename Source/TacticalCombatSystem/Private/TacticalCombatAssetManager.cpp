// Copyright  CtrlShiftSpace


#include "TacticalCombatAssetManager.h"

#include "TacticalCombatGameplayTags.h"

UTacticalCombatAssetManager& UTacticalCombatAssetManager::Get()
{
	UTacticalCombatAssetManager* TacticalCombatAssetManager = Cast<UTacticalCombatAssetManager>(&UAssetManager::Get());
	return *TacticalCombatAssetManager;
}

void UTacticalCombatAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FTacticalCombatGameplayTags::InitializeNativeGameplayTags();
}




