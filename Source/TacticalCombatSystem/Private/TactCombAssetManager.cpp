// Copyright  CtrlShiftSpace


#include "TactCombAssetManager.h"

#include "TactCombGameplayTags.h"

UTactCombAssetManager& UTactCombAssetManager::Get()
{
	UTactCombAssetManager* TacticalCombatAssetManager = Cast<UTactCombAssetManager>(&UAssetManager::Get());
	return *TacticalCombatAssetManager;
}

void UTactCombAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FTactCombGameplayTags::InitializeNativeGameplayTags();
}




