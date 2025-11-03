// Copyright  CtrlShiftSpace


#include "Character/TactCombCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATactCombCharacterBase::ATactCombCharacterBase()
{
	// 取消使用 Tick
	PrimaryActorTick.bCanEverTick = false;
	
}

// Called when the game starts or when spawned
void ATactCombCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	
}

