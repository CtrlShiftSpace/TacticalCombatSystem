// Copyright  CtrlShiftSpace


#include "Actor/GridActor/TactCombGridObstacle.h"

ATactCombGridObstacle::ATactCombGridObstacle()
{
	GridMesh->SetHiddenInGame(true);
	GridMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// 設定為障礙物網格類型
	GridTileType = EGridTileType::Obstacle;
}

void ATactCombGridObstacle::UpdateGridShape(const UGridClassInfo* GridClassInfo)
{
	if (GridClassInfo != nullptr)
	{
		const FGridClassAssetInfo& GridAssetInfo = GridClassInfo->GetGridClassAssetInfo(GridShape);
		if (GridAssetInfo.GridMesh != nullptr)
		{
			GridMesh->SetStaticMesh(GridAssetInfo.GridMesh);
			if (GridAssetInfo.GridMeshMaterial != nullptr)
			{
				GridMesh->SetMaterial(0, GridAssetInfo.GridFlatFilledMaterial);
			}
		}
	}
	else
	{
		GridMesh->SetStaticMesh(nullptr);
	}
}


