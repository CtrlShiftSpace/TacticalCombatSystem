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
	// 設定玩家角色等級
	void SetCharacterLevel(int32 InCharacterLevel);
	void SetMaxHealth(int32 InMaxHealth);
	void SetHealth(int32 InHealth);

	// 取得玩家名稱
	FString GetPlayerName() const;
	// 取得玩家角色等級
	int32 GetCharacterLevel() const;
	int32 GetMaxHealth() const;
	int32 GetHealth() const;

private:

	// 玩家名稱
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	FString PlayerName;

	// 玩家角色等級
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	int32 CharacterLevel;

	// 玩家最大HP
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	int32 MaxHealth;

	// 玩家HP
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess="true"))
	int32 Health;
};
