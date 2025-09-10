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
	GridInstParam.LeftBottomCornerLocation = GetLeftBottomCornerLocation();
	const UGridClassInfo* GridClassInfo =  UTactCombAbilitySystemLibrary::GetGridClassInfo(this);
	SpawnGridInstance(GridClassInfo);
}

void ATactCombGridInstActor::SpawnGridInstance(const UGridClassInfo* GridClassInfo)
{
	// 依照設定的形狀取得網格的素材
	const FGridClassAssetInfo& GridAssetInfo = GridClassInfo->GetGridClassAssetInfo(GridShape);
	// 計算網格的縮放比例
	const FVector GridScale = GetGridScale(GridClassInfo);
	const FVector2D GridPlaneSize = GetGridPlaneSize();
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
			const FVector InstanceLocation = LeftBottomCornerLocation + FVector(GridPlaneSize.X * X, GridPlaneSize.Y * Y, 0.f);
			const FTransform InstanceTransform = FTransform(
				InstanceRotator,
				InstanceLocation,
				GridScale
			);
			GridInstMesh->AddInstance(InstanceTransform);
		}
	}
}

FVector2D ATactCombGridInstActor::GetGridPlaneSize() const
{
	// 計算網格平面大小，只取XY值
	FVector2D GridPlaneSize = FVector2D(GridInstParam.GridSize);
	if (GridShape == EGridShape::Triangle)
	{
		// 三角形的 Y 軸長度較短需要除以 2
		GridPlaneSize.Y *= 0.5f;
	}
	return GridPlaneSize;
}

FVector2D ATactCombGridInstActor::GetHalfPlaneSize() const
{
	const FVector2D GridPlaneSize = GetGridPlaneSize();
	// 計算網格平面大小的一半
	return FVector2D(
		GridInstParam.LengthGridNum - 1 > 0 ? GridInstParam.LengthGridNum - 1 : 0,
		GridInstParam.WidthGridNum - 1 > 0 ? GridInstParam.WidthGridNum - 1 : 0
		) * 0.5f * GridPlaneSize;
}

FVector ATactCombGridInstActor::GetLeftBottomCornerLocation() const
{
	const FVector2D HalfGridPlaneSize = GetHalfPlaneSize();
	return GridInstParam.CenterLocation - FVector(HalfGridPlaneSize.X, HalfGridPlaneSize.Y, 0.f);
}
