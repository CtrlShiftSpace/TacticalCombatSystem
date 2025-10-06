// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TactCombGameModeBase.generated.h"

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
	
};
