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

void ATactCombGridInstActor::BeginPlay()
{
	Super::BeginPlay();
	// 更新網格左下角位置
	const UGridClassInfo* GridClassInfo =  UTactCombAbilitySystemLibrary::GetGridClassInfo(this);
	SpawnGridInstance(GridClassInfo);
}

void ATactCombGridInstActor::SpawnGridInstance(const UGridClassInfo* GridClassInfo)
{
	GridInstParam.LeftBottomCornerLocation = GetLeftBottomCornerLocation();
	// 依照設定的形狀取得網格的素材
	const FGridClassAssetInfo& GridAssetInfo = GridClassInfo->GetGridClassAssetInfo(GridShape);
	// 計算網格的縮放比例
	const FVector GridScale = GetGridScale(GridClassInfo);
	const FVector2D GridTileSize = GetGridTileSize();
	// 取得網格平面左下角的座標位置
	const FVector& LeftBottomCornerLocation = GridInstParam.LeftBottomCornerLocation;
	// 移除現有的 Instance 資訊
	GridInstMesh->ClearInstances();
	// 使用 Border 的 Mesh
	UStaticMesh* InstanceMesh = GridAssetInfo.GridFlatMesh;
	GridInstMesh->SetStaticMesh(InstanceMesh);
	GridInstMesh->SetMaterial(0, GridAssetInfo.GridFlatBorderMaterial);
	
	// 從左下位置依序建立網格
	for (int32 X = 0; X < GridInstParam.LengthGridNum; ++X)
	{
		FVector InstanceOffset = FVector::ZeroVector;
		// 六邊形的判斷
		if (GridShape == EGridShape::Hexagon)
		{
			// 如果是奇數列，則需要半個格子的偏移
			if (FMath::Modulo(X, 2) == 1)
			{
				InstanceOffset.Y = GridTileSize.Y * 0.5f;
			}
		}

		for (int32 Y = 0; Y < GridInstParam.WidthGridNum; ++Y)
		{
			FRotator InstanceRotator = FRotator::ZeroRotator;
			// 三角形的判斷
			if (GridShape == EGridShape::Triangle)
			{
				bool bXOdd = (FMath::Modulo(X, 2) == 1);
                bool bYOdd = (FMath::Modulo(Y, 2) == 1);
				// 只有 X 與 Y 其中一個是奇數，才旋轉 180 度
				if (bXOdd != bYOdd)
				{
					InstanceRotator = FRotator(0.f, 180.f, 0.f);
				}
			}
			
			const FVector InstanceLocation = LeftBottomCornerLocation + FVector(GridTileSize.X * X, GridTileSize.Y * Y, 0.f) + InstanceOffset;
			const FTransform InstanceTransform = FTransform(
				InstanceRotator,
				InstanceLocation,
				GridScale
			);
			GridInstMesh->AddInstance(InstanceTransform);
		}
	}
}

FVector2D ATactCombGridInstActor::GetGridTileSize() const
{
	// 計算網格平面大小，只取XY值
	FVector2D GridTileSize = FVector2D(GridInstParam.GridSize);
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
	return FVector2D(GridInstParam.LengthGridNum, GridInstParam.WidthGridNum) * GridTileSize;
}

FVector ATactCombGridInstActor::GetLeftBottomCornerLocation() const
{
	const FVector2D HalfGridPlaneSize = FVector2D(
		GridInstParam.LengthGridNum - 1 > 0 ? (GetGridTileSize().X * (GridInstParam.LengthGridNum - 1)) : 0.f,
		GridInstParam.WidthGridNum - 1 > 0 ? (GetGridTileSize().Y * (GridInstParam.WidthGridNum - 1)) : 0.f
	) * 0.5f;
	return GridInstParam.CenterLocation - FVector(HalfGridPlaneSize.X, HalfGridPlaneSize.Y, 0.f);
}
