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

	// Grid Tag
	
	GameplayTags.Grid_Shape_Triangle = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Grid.Shape.Triangle"),
		FString("Grid Tag for Triangle Shape")
	);

	GameplayTags.Grid_Shape_Square = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Grid.Shape.Square"),
		FString("Grid Tag for Square Shape")
	);

	GameplayTags.Grid_Shape_Hexagon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Grid.Shape.Hexagon"),
		FString("Grid Tag for Hexagon Shape")
	);

}
