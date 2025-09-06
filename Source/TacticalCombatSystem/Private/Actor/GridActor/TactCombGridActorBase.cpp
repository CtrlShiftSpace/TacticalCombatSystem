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

