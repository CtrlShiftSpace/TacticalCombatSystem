// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TactCombAbilitySystemLibrary.generated.h"

class UGridClassInfo;
/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API UTactCombAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	// 取得網格相關設定資訊
	UFUNCTION(BlueprintCallable, Category = "TactCombAbilitySystemLibrary|GridClassInfo")
	static UGridClassInfo* GetGridClassInfo(const UObject* WorldContextObject);
	
};
