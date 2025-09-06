// Copyright  CtrlShiftSpace


#include "Actor/GridActor/TactCombGridActor.h"

ATactCombGridActor::ATactCombGridActor()
{
	// 建立靜態網格元件
	GridMesh = CreateDefaultSubobject<UStaticMeshComponent>("GridMesh");
	GridMesh->SetupAttachment(RootComponent);
}

void ATactCombGridActor::BeginPlay()
{
	Super::BeginPlay();
}
