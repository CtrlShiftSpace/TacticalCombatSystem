// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "UI/ViewModel/MVVM_ScreenBase.h"
#include "MVVM_Overlay.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API UMVVM_Overlay : public UMVVM_ScreenBase
{
	GENERATED_BODY()

public:

	// 設定玩家名稱
	void SetPlayerName(FString InPlayerName);

	// 取得玩家名稱
	FString GetPlayerName() const;

private:

	// 玩家名稱
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	FString PlayerName;
	
};
