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

