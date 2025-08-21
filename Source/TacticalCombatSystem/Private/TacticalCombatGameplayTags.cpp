// Copyright  CtrlShiftSpace

#include "TacticalCombatGameplayTags.h"
#include "GameplayTagsManager.h"

// 靜態變數初始化
FTacticalCombatGameplayTags FTacticalCombatGameplayTags::GameplayTags;

const FTacticalCombatGameplayTags& FTacticalCombatGameplayTags::Get()
{
	return GameplayTags;
}

void FTacticalCombatGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.InputTag_Zoom_In = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Zoom.In"),
		FString("Input Tag for Zooming In")
	);
	
	GameplayTags.InputTag_Zoom_Out = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Zoom.Out"),
		FString("Input Tag for Zooming Out")
	);
}
