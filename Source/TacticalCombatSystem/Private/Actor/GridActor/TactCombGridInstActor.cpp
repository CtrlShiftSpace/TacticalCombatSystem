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
	const UGridClassInfo* GridClassInfo =  UTactCombAbilitySystemLibrary::GetGridClassInfo(this);
	SpawnGridInstance(GridInstParam, GridClassInfo);
}

void ATactCombGridInstActor::SpawnGridInstance(const FGridInstanceParam& InGridInstParam, const UGridClassInfo* GridClassInfo)
{
	const float ScaleDist = 0.5f;
	// 計算網格總大小的一半
	const FVector2D HalfGridSizeXY = FVector2D(InGridInstParam.WidthGridNum ,InGridInstParam.LengthGridNum) * FVector2D(InGridInstParam.GridSize.X, InGridInstParam.GridSize.Y) / 2;
	// 計算左下角的座標
	const FVector LeftBottomCornerLocation = InGridInstParam.CenterLocation - FVector(HalfGridSizeXY.X, HalfGridSizeXY.Y, 0.f);

	// 依照設定的形狀取得網格的素材
	FGridClassAssetInfo GridAssetInfo = GridClassInfo->GetGridClassAssetInfo(GridShape);
	// 使用 Border 的 Mesh
	UStaticMesh* InstanceMesh = GridAssetInfo.GridMesh;
	GridInstMesh->SetStaticMesh(InstanceMesh);
	GridInstMesh->SetMaterial(0, GridAssetInfo.GridFlatBorderMaterial);
	
	// 從左下位置依序建立網格
	for (int32 X = 0; X < InGridInstParam.WidthGridNum; ++X)
	{
		for (int32 Y = 0; Y < InGridInstParam.LengthGridNum; ++Y)
		{
			const FVector InstanceLocation = LeftBottomCornerLocation + FVector(InGridInstParam.GridSize.X * (X + ScaleDist), InGridInstParam.GridSize.Y * (Y + ScaleDist), 0.f);
			const FTransform InstanceTransform = FTransform(
				FRotator::ZeroRotator,
				InstanceLocation,
				InGridInstParam.GridSize / GridAssetInfo.MeshSize
			);
			GridInstMesh->AddInstance(InstanceTransform);
		}
	}
}
