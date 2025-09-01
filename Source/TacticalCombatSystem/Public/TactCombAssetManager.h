// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TactCombAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API UTactCombAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	/**
	 * 獲取 TactCombAssetManager 的實例
	 * 
	 * @return 返回 TactCombAssetManager 的實例
	 * @note 雖然 UAssetManager 也有定義 Get()，但由於是 static 方法，不會透過物件方式呼叫，因此不會互相影響也不會繼承
	 */
	static UTactCombAssetManager& Get();
	
protected:
	/**
	 * 初始載入時的處理函式
	 *
	 * @return 無回傳值
	 */
	virtual void StartInitialLoading() override;
	
	
};
