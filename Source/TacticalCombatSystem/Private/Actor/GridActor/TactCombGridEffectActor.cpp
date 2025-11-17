// Copyright  CtrlShiftSpace


#include "Actor/GridActor/TactCombGridEffectActor.h"

#include "Interaction/PlayerInterface.h"

ATactCombGridEffectActor::ATactCombGridEffectActor()
{
	
}

void ATactCombGridEffectActor::OnOverlap(AActor* TargetActor)
{
	if (TargetActor->Implements<UPlayerInterface>())
	{
		const FPlayerAbilityInfo PlayerAbilityInfo = IPlayerInterface::Execute_GetPlayerAbilityInfo(TargetActor);
		GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString::Printf(TEXT("Value: %d"), PlayerAbilityInfo.PlayerLevel));
	}
}

void ATactCombGridEffectActor::OnEndOverlap(AActor* TargetActor)
{
}
