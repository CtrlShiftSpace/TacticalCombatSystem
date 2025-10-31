// Copyright  CtrlShiftSpace


#include "Game/TactCombGameModeBase.h"

#include "Actor/GridActor/TactCombGridInstActor.h"

void ATactCombGameModeBase::ShowGridInstActor(const FTransform& InTrans)
{
	// GridInstClass 尚未設定
	checkf(GridInstClass, TEXT("GridInstClass is not set"));

	if (GridInstActor == nullptr)
	{
		// 使用 SpawnActorDeferred 會等到設定完相關參數執行 FinishSpawning 才生成
		// 確保生成時已經是預期的狀態
		GridInstActor = GetWorld()->SpawnActorDeferred<ATactCombGridInstActor>(
			GridInstClass,
			InTrans,
			this,
			nullptr,
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
		);

		// 確認 GridInstActor 存在
		if (GridInstActor)
		{
			GridInstActor->SpawnGridInstance(GridClassInfo);
			GridInstActor->FinishSpawning(InTrans);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn GridInstActor"));
			return;
		}
	}
	GridInstActor->SetActorHiddenInGame(false);
	GridInstActor->SetActorEnableCollision(true);
}

void ATactCombGameModeBase::HideGridInstActor()
{
	if (GridInstActor == nullptr)
	{
		return;
	}
	GridInstActor->SetActorHiddenInGame(true);
	GridInstActor->SetActorEnableCollision(false);
}
