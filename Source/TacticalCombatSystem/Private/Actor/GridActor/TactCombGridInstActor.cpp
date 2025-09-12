// Copyright  CtrlShiftSpace


#include "Actor/GridActor/TactCombGridInstActor.h"

#include "AbilitySystem/TactCombAbilitySystemLibrary.h"
#include "Components/InstancedStaticMeshComponent.h"

ATactCombGridInstActor::ATactCombGridInstActor()
{
	// 建立靜態網格元件
	GridInstMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("GridInstMesh");
	GridInstMesh->SetupAttachment(RootComponent);
}

TArray<FGridInstanceTile> ATactCombGridInstActor::GetGridInstTiles(const UGridClassInfo* GridClassInfo)
{
	LeftBottomCornerLocation = GetLeftBottomCornerLocation();
	const FGridClassAssetInfo& GridAssetInfo = GridClassInfo->GetGridClassAssetInfo(GridShape);
	// 計算網格的縮放比例
	const FVector GridScale = GetGridScale(GridClassInfo) * GridSize / GridAssetInfo.MeshSize;
	const FVector2D GridTileSize = GetGridTileSize();
	TArray<FGridInstanceTile> GridInstTilesRecord;
	
	// 從左下位置依序建立網格
	for (int32 X = 0; X < LengthGridNum; ++X)
	{
		// 計算額外要增加的偏移量
		FVector InstanceOffset = FVector::ZeroVector;
		// X 是否為奇數
		const bool bXOdd = (FMath::Modulo(X, 2) == 1);
		// 如果是奇數列且為六邊形
		if (bXOdd && GridShape == EGridShape::Hexagon)
		{
			// 需要半個格子的偏移
			InstanceOffset.Y = GridTileSize.Y * 0.5f;
		}

		for (int32 Y = 0; Y < WidthGridNum; ++Y)
		{
			FRotator InstanceRotator = FRotator::ZeroRotator;
			// Y 是否為奇數
			const bool bYOdd = (FMath::Modulo(Y, 2) == 1);
			// 三角形的判斷
			if (GridShape == EGridShape::Triangle)
			{
				// 只有 X 與 Y 其中一個是奇數，才旋轉 180 度
				if (bXOdd != bYOdd)
				{
					InstanceRotator = FRotator(0.f, 180.f, 0.f);
				}
			}

			// 最左下座標 + (X * 格子長度, Y * 格子寬度) + 偏移量 + 額外偏移量
			const FVector InstanceLocation = LeftBottomCornerLocation +
												FVector(GridTileSize.X * X, GridTileSize.Y * Y, 0.f) +
												InstanceOffset + TileOffsetVector;
			FGridInstanceTile GridInstTile;
			GridInstTile.TileTransform = FTransform(
				InstanceRotator,
				InstanceLocation,
				GridScale
			);
			GridInstTilesRecord.Add(GridInstTile);
		}
	}
	return GridInstTilesRecord;
}

void ATactCombGridInstActor::BeginPlay()
{
	Super::BeginPlay();
	// 更新網格左下角位置
	const UGridClassInfo* GridClassInfo =  UTactCombAbilitySystemLibrary::GetGridClassInfo(this);
	SpawnGridInstance(GridClassInfo);
}

void ATactCombGridInstActor::SpawnGridInstance(const UGridClassInfo* GridClassInfo)
{
	// 依照設定的形狀取得網格的素材
	const FGridClassAssetInfo& GridAssetInfo = GridClassInfo->GetGridClassAssetInfo(GridShape);
	// 移除現有的 Instance 資訊
	GridInstMesh->ClearInstances();
	// 使用 Border 的 Mesh
	UStaticMesh* InstanceMesh = GridAssetInfo.GridFlatMesh;
	GridInstMesh->SetStaticMesh(InstanceMesh);
	GridInstMesh->SetMaterial(0, GridAssetInfo.GridFlatBorderMaterial);

	// 長或寬小於等於 0 無法生成網格
	if (LengthGridNum <= 0 || WidthGridNum <= 0)
	{
		return;
	}

	// 取得要生成的網格資訊
	GridInstTiles = GetGridInstTiles(GridClassInfo);
	// 依序加入 Instance
	for (const FGridInstanceTile& GridInstTile : GridInstTiles)
	{
		GridInstMesh->AddInstance(GridInstTile.TileTransform);
	}

	// // 測試偵測線段
	// FVector DetectGroundStart = InstanceLocation + FVector(0.f, 0.f, 500.f);
	// FVector DetectGroundEnd = InstanceLocation + FVector(0.f, 0.f, -500.f);
	// // 轉換到世界座標
	// FVector DetectGroundInWorldStart = GetActorTransform().TransformPosition(DetectGroundStart);
	// FVector DetectGroundInWorldEnd = GetActorTransform().TransformPosition(DetectGroundEnd);
	// 		
	// const TArray<AActor*>& ActorsToIgnore = TArray<AActor*>();
	// FHitResult HitResult;
	// const bool bDetectGround = UKismetSystemLibrary::LineTraceSingle(this, DetectGroundInWorldStart, DetectGroundInWorldEnd, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);
	// if (bDetectGround)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Ground Location: %s"), *HitResult.ImpactPoint.ToString()));
	// }
	// 		
	// DrawDebugLine(GetWorld(), DetectGroundInWorldStart, DetectGroundInWorldEnd, FColor::Green, true, -1.f, 0, 5.f);
}

FVector2D ATactCombGridInstActor::GetGridTileSize() const
{
	// 計算網格平面大小，只取XY值
	FVector2D GridTileSize = FVector2D(GridSize);
	if (GridShape == EGridShape::Triangle)
	{
		// 三角形的 Y 軸長度較短需要除以 2
		GridTileSize.Y *= 0.5f;
	}else if (GridShape == EGridShape::Hexagon)
	{
		// 六邊形的 X 軸長度較短需要乘以 0.75
		GridTileSize.X *= 0.75f;
	}
	return GridTileSize;
}

FVector2D ATactCombGridInstActor::GetGridPlaneSize() const
{
	const FVector2D GridTileSize = GetGridTileSize();
	return FVector2D(LengthGridNum, WidthGridNum) * GridTileSize;
}

FVector ATactCombGridInstActor::GetLeftBottomCornerLocation() const
{
	const FVector2D HalfGridPlaneSize = FVector2D(
		LengthGridNum - 1 > 0 ? (GetGridTileSize().X * (LengthGridNum - 1)) : 0.f,
		WidthGridNum - 1 > 0 ? (GetGridTileSize().Y * (WidthGridNum - 1)) : 0.f
	) * 0.5f;
	return CenterLocation - FVector(HalfGridPlaneSize.X, HalfGridPlaneSize.Y, 0.f);
}
