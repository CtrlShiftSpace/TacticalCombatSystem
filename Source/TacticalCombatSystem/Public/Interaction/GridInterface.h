// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GridInterface.generated.h"

// 網格類型
UENUM()
enum class EGridTileType : uint8
{
	None,
	Accessible,
	Obstacle
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGridInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TACTICALCOMBATSYSTEM_API IGridInterface
{
	GENERATED_BODY()

public:

	// 取得網格類型
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Grid Interface")
	EGridTileType GetGridTileType() const;

	// 取得網格軸點位置，軸點不一定是中心點
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Grid Interface")
	FVector GetGridPivotLocation() const;

	// 透過傳入位置取得最近的軸點位置
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Grid Interface")
	FVector GetNearestPivotByLocation(const FVector& InLocation) const;
	
};
