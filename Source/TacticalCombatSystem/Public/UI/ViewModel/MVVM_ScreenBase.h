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
	FViewModelScreenParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
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

	UPROPERTY(BlueprintReadOnly, Category = "MVVM|ScreenBase")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "MVVM|ScreenBase")
	TObjectPtr<UAttributeSet> AttributeSet;
};
