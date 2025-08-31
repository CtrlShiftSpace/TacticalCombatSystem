// Copyright  CtrlShiftSpace

#include "TactCombGameplayTags.h"
#include "GameplayTagsManager.h"

// 靜態變數初始化
FTactCombGameplayTags FTactCombGameplayTags::GameplayTags;

const FTactCombGameplayTags& FTactCombGameplayTags::Get()
{
	return GameplayTags;
}

void FTactCombGameplayTags::InitializeNativeGameplayTags()
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
