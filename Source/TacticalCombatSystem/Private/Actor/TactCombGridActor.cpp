// Copyright  CtrlShiftSpace


#include "Actor/TactCombGridActor.h"
#include "AbilitySystem/TactCombAbilitySystemLibrary.h"

// Sets default values
ATactCombGridActor::ATactCombGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// 建立靜態網格元件
	GridMesh = CreateDefaultSubobject<UStaticMeshComponent>("GridMesh");
	GridMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATactCombGridActor::BeginPlay()
{
	Super::BeginPlay();

	// 取得目前設定的網格 Material
	GridClassInfo = UTactCombAbilitySystemLibrary::GetGridClassInfo(this);
	const FGridClassAssetInfo& GridClassAssetInfo = GridClassInfo->GetGridClassAssetInfo(GridShape);

	// 如果 Mesh 存在才設定網格素材
	if (GridMesh->GetStaticMesh() != nullptr && GridMesh->GetNumMaterials() > 0)
	{
		GridMesh->SetMaterial(0, GridClassAssetInfo.GridMaterial);
	}
}

