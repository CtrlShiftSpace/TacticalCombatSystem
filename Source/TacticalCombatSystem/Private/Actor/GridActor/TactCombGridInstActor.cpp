// Copyright  CtrlShiftSpace


#include "Actor/GridActor/TactCombGridInstActor.h"
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
}

void ATactCombGridInstActor::SpawnGridInstance(const FGridInstanceParam& InGridInstParam)
{
	const float ScaleDist = 0.5f;
	// 計算網格總大小的一半
	const FVector2D HalfGridSizeXY = FVector2D(InGridInstParam.WidthGridNum ,InGridInstParam.LengthGridNum) * FVector2D(InGridInstParam.GridSize.X, InGridInstParam.GridSize.Y) / 2;
	// 計算左下角的座標
	const FVector LeftBottomCornerLocation = InGridInstParam.CenterLocation - FVector(HalfGridSizeXY.X, HalfGridSizeXY.Y, 0.f);

	// 從左下位置依序建立網格
	for (int32 X = 0; X < InGridInstParam.WidthGridNum; ++X)
	{
		for (int32 Y = 0; Y < InGridInstParam.LengthGridNum; ++Y)
		{
			const FVector InstanceLocation = LeftBottomCornerLocation + FVector(InGridInstParam.GridSize.X * (X + ScaleDist), InGridInstParam.GridSize.Y * (Y + ScaleDist), 0.f);
			const FTransform InstanceTransform = FTransform(FRotator::ZeroRotator, InstanceLocation, FVector(InGridInstParam.GridSize.X / 100.f, InGridInstParam.GridSize.Y / 100.f, 1.f));
			GridInstMesh->AddInstance(InstanceTransform);
		}
	}
}
