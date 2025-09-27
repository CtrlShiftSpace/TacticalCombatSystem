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
	
	// 透過索引值取得軸點位置
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Grid Interface")
	FVector GetPivotByIndex(int32 Index) const;

	
};
