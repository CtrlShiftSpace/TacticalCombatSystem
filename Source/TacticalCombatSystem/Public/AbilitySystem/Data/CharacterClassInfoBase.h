// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfoBase.generated.h"

class UGameplayEffect;

// 角色職業類型
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Warrior,
	Ranger
};

// 各角色職業中需要記錄的資訊
USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	// 基礎屬性
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	// 衍生屬性
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	// 生存相關屬性
	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;
	
};

/**
 * 
 */
UCLASS(Abstract)
class TACTICALCOMBATSYSTEM_API UCharacterClassInfoBase : public UDataAsset
{
	GENERATED_BODY()

public:

	// 取得指定職業中具備的資料
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);
	
protected:

	// 對應不同職業中的相關資訊，主要包含像是力量、敏捷等數值
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;


	
};
