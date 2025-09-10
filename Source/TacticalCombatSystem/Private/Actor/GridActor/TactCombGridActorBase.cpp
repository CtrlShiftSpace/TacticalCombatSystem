// Copyright  CtrlShiftSpace


#include "Actor/GridActor/TactCombGridActorBase.h"
#include "AbilitySystem/TactCombAbilitySystemLibrary.h"

ATactCombGridActorBase::ATactCombGridActorBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

FGameplayTag ATactCombGridActorBase::GetGridShapeTag() const
{
	return GridShapeTag;
}

FVector ATactCombGridActorBase::GetSnapGridPosition(const FVector& InLocation, const FVector& GridSize, const FVector& GridOffset) const
{
	return FVector(
			FMath::GridSnap(InLocation.X, GridSize.X),
			FMath::GridSnap(InLocation.Y, GridSize.Y),
			FMath::GridSnap(InLocation.Z, GridSize.Z)
			) + GridOffset;
}

// Called when the game starts or when spawned
void ATactCombGridActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (const UGridClassInfo* GridClassInfo = UTactCombAbilitySystemLibrary::GetGridClassInfo(this))
	{
		// 設定網格形狀的 Gameplay Tag
		GridShapeTag = GridClassInfo->GetGridClassAssetInfo(GridShape).GridShapeTag;
	}
}

FVector ATactCombGridActorBase::GetGridScale(const UGridClassInfo* GridClassInfo) const
{
	// 依照設定的形狀取得網格的素材
	const FGridClassAssetInfo& GridAssetInfo = GridClassInfo->GetGridClassAssetInfo(GridShape);
	if (GridAssetInfo.GridMesh && GridAssetInfo.GridMesh->GetRenderData())
	{
		// 取得原始素材的長寬高
		const FBox BoundingBox = GridAssetInfo.GridMesh->GetRenderData()->Bounds.GetBox();
		const FVector AssetSize = BoundingBox.GetSize();
		// 計算縮放比例，並四捨五入到小數點後兩位
		return FVector(
			(GridAssetInfo.MeshSize.X != 0.f) ? FMath::RoundToInt32(GridAssetInfo.MeshSize.X / AssetSize.X * 100.f) / 100.f : 1.f,
			(GridAssetInfo.MeshSize.Y != 0.f) ? FMath::RoundToInt32(GridAssetInfo.MeshSize.Y / AssetSize.Y * 100.f) / 100.f : 1.f,
			(GridAssetInfo.MeshSize.Z != 0.f) ? FMath::RoundToInt32(GridAssetInfo.MeshSize.Z / AssetSize.Z * 100.f) / 100.f : 1.f
		);
	}
	// 網格 Mesh 模型對於預期網格大小的縮放，預設倍率為1
	return FVector::OneVector;
}

