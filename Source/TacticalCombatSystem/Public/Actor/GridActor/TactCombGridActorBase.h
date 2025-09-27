// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/GridClassInfo.h"
#include "GameFramework/Actor.h"
#include "Interaction/GridInterface.h"
#include "TactCombGridActorBase.generated.h"

enum class EGridShape : uint8;

UCLASS(Abstract)
class TACTICALCOMBATSYSTEM_API ATactCombGridActorBase : public AActor, public IGridInterface
{
	GENERATED_BODY()
	
public:
	ATactCombGridActorBase();

	// 取得識別網格形狀的 Gameplay Tag
	UFUNCTION(BlueprintCallable, Category = "Grid Class Info")
	FGameplayTag GetGridShapeTag() const;

	// 計算傳入位置對齊到網格後的位置
	UFUNCTION(BlueprintCallable, Category = "Grid Process")
	FVector GetSnapGridPosition(const FVector& InLocation, const FVector& GridSize, const FVector& GridOffset = FVector::ZeroVector) const;

	/* 覆寫 GridInterface 介面 */
	virtual EGridTileType GetGridTileType_Implementation() const override;
	virtual FVector GetPivotByIndex_Implementation(int32 Index) const override;
	/* 覆寫 GridInterface 介面 End */
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 呈現網格形狀
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Class Info")
	EGridShape GridShape = EGridShape::Square;

	// 網格形狀的 Gameplay Tag
	FGameplayTag GridShapeTag;

	// 取得網格對應素材的縮放比例
	FVector GetGridScale(const UGridClassInfo* GridClassInfo) const;

	// 網格類型(包含是否可行走、被阻擋)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid Class Info")
	EGridTileType GridTileType = EGridTileType::None;
	
private:

	
};
