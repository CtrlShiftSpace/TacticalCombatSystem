// Copyright  CtrlShiftSpace


#include "Actor/GridActor/TactCombGridInstActor.h"

#include "AbilitySystem/TactCombAbilitySystemLibrary.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Math/TransformCalculus3D.h"

ATactCombGridInstActor::ATactCombGridInstActor()
{
	// 建立靜態網格元件
	GridInstMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>("GridInstMesh");
	GridInstMesh->SetupAttachment(RootComponent);
}

void ATactCombGridInstActor::BeginPlay()
{
	Super::BeginPlay();
	const UGridClassInfo* GridClassInfo =  UTactCombAbilitySystemLibrary::GetGridClassInfo(this);
	SpawnGridInstance(GridInstParam, GridClassInfo);
}

void ATactCombGridInstActor::SpawnGridInstance(const FGridInstanceParam& InGridInstParam, const UGridClassInfo* GridClassInfo)
{
	// 依照設定的形狀取得網格的素材
	const FGridClassAssetInfo& GridAssetInfo = GridClassInfo->GetGridClassAssetInfo(GridShape);
	// 計算網格的縮放比例
	const FVector GridScale = InGridInstParam.GridSize / GridAssetInfo.MeshSize * 2.f;
	// 計算網格平面大小
	FVector2D GridPlaneSize = FVector2D(InGridInstParam.GridSize.X, InGridInstParam.GridSize.Y);
	if (GridShape == EGridShape::Triangle)
	{
		// 三角形的 Y 軸長度較短需要除以 2
		GridPlaneSize.Y *= 0.5f;
	}

	// 計算網格總大小的一半
	const FVector2D HalfGridSizeXY = FVector2D(InGridInstParam.WidthGridNum - 1, InGridInstParam.LengthGridNum - 1) * 0.5f * GridPlaneSize;
	// 計算左下角的座標
	const FVector LeftBottomCornerLocation = InGridInstParam.CenterLocation - FVector(HalfGridSizeXY.X, HalfGridSizeXY.Y, 0.f);
	// 移除現有的 Instance 資訊
	GridInstMesh->ClearInstances();
	// 使用 Border 的 Mesh
	UStaticMesh* InstanceMesh = GridAssetInfo.GridFlatMesh;
	GridInstMesh->SetStaticMesh(InstanceMesh);
	GridInstMesh->SetMaterial(0, GridAssetInfo.GridFlatBorderMaterial);
	
	// 從左下位置依序建立網格
	for (int32 X = 0; X < InGridInstParam.WidthGridNum; ++X)
	{
		for (int32 Y = 0; Y < InGridInstParam.LengthGridNum; ++Y)
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
