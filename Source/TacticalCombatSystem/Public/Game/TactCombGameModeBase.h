// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TactCombGameModeBase.generated.h"

class ATactCombGridInstActor;
class ATactCombCharacter;
class UGridClassInfo;
/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	// 設定的網格類別資訊
	UPROPERTY(EditDefaultsOnly, Category = "Grid Class")
	TObjectPtr<UGridClassInfo> GridClassInfo;

	// 在指定位置顯示網格
	void ShowGridInstActor(const FTransform& InTrans);

	// 隱藏網格
	void HideGridInstActor();
	
protected:

	// 用來顯示網格物件
	UPROPERTY()
	TObjectPtr<ATactCombGridInstActor> GridInstActor;
	
	// 用來顯示網格類別
	UPROPERTY(EditDefaultsOnly, Category = "Grid Class")
	TSubclassOf<ATactCombGridInstActor> GridInstClass;
};
