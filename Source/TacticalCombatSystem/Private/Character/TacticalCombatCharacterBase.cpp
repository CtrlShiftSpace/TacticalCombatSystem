// Copyright  CtrlShiftSpace


#include "Character/TacticalCombatCharacterBase.h"

// Sets default values
ATacticalCombatCharacterBase::ATacticalCombatCharacterBase()
{
	// 取消使用 Tick
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATacticalCombatCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

