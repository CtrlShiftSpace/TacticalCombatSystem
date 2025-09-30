// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FTactCombGameplayTags
{

public:
	/**
	 * 取得 FTactCombGameplayTags 的單例實例
	 * 
	 * @return 靜態的 FTacticalCombatGameplayTags 實例
	 * @note 這個方法會返回一個靜態的 FTacticalCombatGameplayTags 實例，在整個應用程式中共享相同的 Gameplay Tags。
	 */
	static const FTactCombGameplayTags& Get();
	
	/**
	 * 在 C++ 自定義中所設定的 Gameplay Tag，透過 UGameplayTagsManager 的 AddNativeGameplayTag 加入Gameplay Tag
	 *
	 * @return 無回傳值
	 */
	static void InitializeNativeGameplayTags();

	/**
	 * 初始化 Input Tag
	 * 
	 * @return 無回傳值
	 */
	// static void Initialize_InputTag();
	

	/*
	 * Input Tags
	 */
	
	// 放大
	FGameplayTag InputTag_Zoom_In;
	// 縮小
	FGameplayTag InputTag_Zoom_Out;
	// 與網格互動
	FGameplayTag InputTag_Grid_Interact;

	/*
	 * Grid Tags
	 */
	FGameplayTag Grid_Shape_Triangle;
	FGameplayTag Grid_Shape_Square;
	FGameplayTag Grid_Shape_Hexagon;

private:
	// 使用 static 關鍵字來定義靜態實例，確保只有一個實例存在
	static FTactCombGameplayTags GameplayTags;
};