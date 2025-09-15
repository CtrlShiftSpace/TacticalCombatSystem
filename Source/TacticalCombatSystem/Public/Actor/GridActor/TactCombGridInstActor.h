// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Actor/GridActor/TactCombGridActorBase.h"
#include "TactCombGridInstActor.generated.h"

class UBoxComponent;

USTRUCT(BlueprintType)
struct FGridInstanceTile
{
	GENERATED_BODY()

	// 網格位置
	UPROPERTY()
	FTransform TileTransform = FTransform(FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector);

	// 網格類型
	UPROPERTY()
	EGridTileType TileType = EGridTileType::None;
	
};

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombGridInstActor : public ATactCombGridActorBase
{
	GENERATED_BODY()
	
public:
	ATactCombGridInstActor();

	// 取得網格 Instance Tile
	UFUNCTION()
	TArray<FGridInstanceTile> GetGridInstTiles(const UGridClassInfo* GridClassInfo);

	// 偵測地面資訊
	void DetectGroundInfo(FGridInstanceTile& Tile) const;
	
protected:
	virtual void BeginPlay() override;
	
	// 產生網格 Instance
	UFUNCTION(BlueprintCallable, Category = "GridInst Process")
	void SpawnGridInstance(const UGridClassInfo* GridClassInfo);

	// 取得單一網格大小
	FVector2D GetGridTileSize() const;

	// 取得網格平面大小
	FVector2D GetGridPlaneSize() const;

	// 取得網格平面左下角的座標位置
	FVector GetLeftBottomCornerLocation() const;
		
	// 靜態 Instance 物件
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInstancedStaticMeshComponent> GridInstMesh;

	// 網格大小
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector GridSize = FVector(100.f, 100.f, 100.f);
	
	// 長邊的網格數量
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 LengthGridNum = 5;

	// 寬邊的網格數量
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 WidthGridNum = 4;

	// 偵測地面的最大高度
	UPROPERTY(EditAnywhere)
	float MaxDetectHeight = 500.f;

	// 偵測地面的最小高度
	UPROPERTY(EditAnywhere)
	float MinDetectHeight = -500.f;

	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;

private:
	// 網格 Instance 的自訂偏移向量，用於浮在地面上，避免同樣高度的物件 Z-Fighting
	UPROPERTY()
	FVector TileOffsetVector = FVector(0.f, 0.f, 2.f);

	// 紀錄每個網格 Instance 的資料
	UPROPERTY()
	TArray<FGridInstanceTile> GridInstTiles;

	// 網格的中心位置
	UPROPERTY()
	FVector CenterLocation = FVector::ZeroVector;

	// 網格的左下角位置
	UPROPERTY()
	FVector LeftBottomCornerLocation = FVector::ZeroVector;
};
