// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TacticalCombatAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API UTacticalCombatAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	/**
	 * 獲取 TacticalCombatAssetManager 的實例
	 * 
	 * @return 返回 TacticalCombatAssetManager 的實例
	 * @note 雖然 UAssetManager 也有定義 Get()，但由於是 static 方法，不會透過物件方式呼叫，因此不會互相影響也不會繼承
	 */
	static UTacticalCombatAssetManager& Get();
	
protected:
	/**
	 * 初始載入時的處理函式
	 *
	 * @return 無回傳值
	 */
	virtual void StartInitialLoading() override;
	
	
};
