// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/GridClassInfo.h"
#include "GameFramework/Actor.h"
#include "TactCombGridActorBase.generated.h"

enum class EGridShape : uint8;

UCLASS(Abstract)
class TACTICALCOMBATSYSTEM_API ATactCombGridActorBase : public AActor
{
	GENERATED_BODY()
	
public:
	ATactCombGridActorBase();

	// 取得識別網格形狀的 Gameplay Tag
	UFUNCTION(BlueprintCallable, Category = "Grid Class Info")
	FGameplayTag GetGridShapeTag() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 呈現網格形狀
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Class Info")
	EGridShape GridShape = EGridShape::Square;

	// 網格形狀的 Gameplay Tag
	FGameplayTag GridShapeTag;
	
private:

	
};
