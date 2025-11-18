// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_ScreenBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FViewModelScreenParams
{
	GENERATED_BODY()

	FViewModelScreenParams(){}
	FViewModelScreenParams(APlayerController* PC, APlayerState* PS) : PlayerController(PC), PlayerState(PS) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState = nullptr;
};

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API UMVVM_ScreenBase : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	// 設定 ViewModel 參數，例如 player controller 或 ASC 等
	UFUNCTION(BlueprintCallable)
	void SetViewModelScreenParams(const FViewModelScreenParams& VMParams);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "MVVM|ScreenBase")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "MVVM|ScreenBase")
	TObjectPtr<APlayerState> PlayerState;
	
};
