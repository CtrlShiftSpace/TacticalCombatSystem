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

FGameplayTag ATactCombGridActor::GetGridShapeTag() const
{
	return GridShapeTag;
}

// Called when the game starts or when spawned
void ATactCombGridActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (const UGridClassInfo* GridClassInfo = UTactCombAbilitySystemLibrary::GetGridClassInfo(this))
	{
		// 設定網格形狀的 Gameplay Tag
		GridShapeTag = GridClassInfo->GetGridClassAssetInfo(GridShape).GridShapeTag;
	}
	
}

