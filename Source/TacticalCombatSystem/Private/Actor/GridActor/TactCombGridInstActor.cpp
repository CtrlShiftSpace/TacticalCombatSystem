// Copyright  CtrlShiftSpace


#include "Actor/GridActor/TactCombGridInstActor.h"

#include "AbilitySystem/TactCombAbilitySystemLibrary.h"
#include "Actor/GridActor/TactCombGridObstacle.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ATactCombGridInstActor::ATactCombGridInstActor()
{
	// 建立靜態網格元件
	GridInstMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("GridInstMesh");
	GridInstMesh->SetupAttachment(RootComponent);
	GridInstMesh->SetNumCustomDataFloats(NumCustomDataFloats);
	if (MaxDetectHeight < MinDetectHeight)
	{
		// 確保最大偵測高度大於最小偵測高度
		MaxDetectHeight = MinDetectHeight;
	}
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
			// 偵測地面資訊
			DetectGroundInfo(GridInstTile);
			GridInstTilesRecord.Add(GridInstTile);
		}
	}
	return GridInstTilesRecord;
}

void ATactCombGridInstActor::DetectGroundInfo(FGridInstanceTile& Tile) const
{
	const FVector& TileLocation = Tile.TileTransform.GetLocation();
	const FVector TileWorldLocation = GetActorTransform().TransformPosition(TileLocation);
	
	// 偵測線段的起點與終點
	const FVector DetectGroundStart = TileLocation + FVector(0.f, 0.f, MaxDetectHeight);
	const FVector DetectGroundEnd = TileLocation + FVector(0.f, 0.f, MinDetectHeight);

	// 將偵測線段轉換到世界座標
	const FVector DetectGroundInWorldStart = GetActorTransform().TransformPosition(DetectGroundStart);
	const FVector DetectGroundInWorldEnd = GetActorTransform().TransformPosition(DetectGroundEnd);

	// 偵測結果
	FHitResult HitResult;
	const bool bDetectGround = UKismetSystemLibrary::LineTraceSingle(this,
									DetectGroundInWorldStart,
									DetectGroundInWorldEnd,
									UEngineTypes::ConvertToTraceType(ECC_Visibility),
									false,
									ActorsToIgnore,
									EDrawDebugTrace::None,
									HitResult,
									true);
	
	if (bDetectGround)
	{
		// 如果有偵測到地面，將地面位置加上偏移量作為更新後的網格位置
		FVector GroundTileLocation = RootComponent->GetComponentTransform().InverseTransformPosition(HitResult.Location) + TileOffsetVector;
		Tile.TileTransform.SetLocation(GroundTileLocation);
		// 檢查是否接觸到實作 GridInterface 介面物件
		if (HitResult.GetActor()->Implements<UGridInterface>())
		{
			// 取得網格類型
			Tile.TileType = IGridInterface::Execute_GetGridTileType(HitResult.GetActor());
		}
	}
}

FVector ATactCombGridInstActor::GetPivotByIndex_Implementation(int32 Index) const
{
	FTransform OutInstanceTransform;
	// 取得 Instance 的 Transform
	if (constexpr bool bWorldSpace = true; GridInstMesh->GetInstanceTransform(Index, OutInstanceTransform, bWorldSpace))
	{
		return OutInstanceTransform.GetLocation();
	}
	return FVector::ZeroVector;
}

void ATactCombGridInstActor::HighlightByIndex(const int32& Index)
{
	Super::HighlightByIndex(Index);
	// 設定高亮顏色
	const FLinearColor HightlightLnColor = HightlightColor.ReinterpretAsLinear();
	if (GridInstMesh->IsValidInstance(Index))
	{
		GridInstMesh->SetCustomDataValue(Index, 0, HightlightLnColor.R, true);
		GridInstMesh->SetCustomDataValue(Index, 1, HightlightLnColor.G, true);
		GridInstMesh->SetCustomDataValue(Index, 2, HightlightLnColor.B, true);
		GridInstMesh->SetCustomDataValue(Index, 3, FillAlpha, true);
	}
}

void ATactCombGridInstActor::UnHighlightByIndex(const int32& Index)
{
	Super::UnHighlightByIndex(Index);
	// 恢復預設顏色
	const FLinearColor DefaultLinearColor = DefaultColor.ReinterpretAsLinear();
	if (GridInstMesh->IsValidInstance(Index))
	{
		GridInstMesh->SetCustomDataValue(Index, 0, DefaultLinearColor.R, true);
		GridInstMesh->SetCustomDataValue(Index, 1, DefaultLinearColor.G, true);
		GridInstMesh->SetCustomDataValue(Index, 2, DefaultLinearColor.B, true);
		GridInstMesh->SetCustomDataValue(Index, 3, UnFillAlpha, true);
	}
}

void ATactCombGridInstActor::SelectedByIndex(const int32& Index)
{
	const FLinearColor SelectedLnColor = SelectedColor.ReinterpretAsLinear();
	if (GridInstMesh->IsValidInstance(Index))
	{
		GridInstMesh->SetCustomDataValue(Index, 0, SelectedLnColor.R, true);
		GridInstMesh->SetCustomDataValue(Index, 1, SelectedLnColor.G, true);
		GridInstMesh->SetCustomDataValue(Index, 2, SelectedLnColor.B, true);
		GridInstMesh->SetCustomDataValue(Index, 3, FillAlpha, true);
	}
}

void ATactCombGridInstActor::DeselectedByIndex(const int32& Index)
{
	Super::DeselectedByIndex(Index);
	UnHighlightByIndex(Index);
}

void ATactCombGridInstActor::BeginPlay()
{
	Super::BeginPlay();
	const UGridClassInfo* GridClassInfo =  UTactCombAbilitySystemLibrary::GetGridClassInfo(this);
	// 將 Actor 位置對齊到格線上
	const FVector GridLocation = GetSnapGridPosition(RootComponent->GetComponentLocation(), GridSize, FVector::ZeroVector);
	// UE_LOG(LogTemp, Log, TEXT("GridLocation: %s"), *GridLocation.ToString());
	RootComponent->SetWorldLocation(GridLocation);
	SpawnGridInstance(GridClassInfo);
}

void ATactCombGridInstActor::SpawnGridInstance(const UGridClassInfo* GridClassInfo)
{
	// 只有 Server 建立
	if (!HasAuthority())
	{
		return;
	}
	
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
		if (GridInstTile.TileType == EGridTileType::Accessible)
		{
			// 只有可到達位置才生成格子
			GridInstMesh->AddInstance(GridInstTile.TileTransform);
		}
	}
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
