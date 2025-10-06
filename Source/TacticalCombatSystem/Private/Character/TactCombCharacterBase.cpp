// Copyright  CtrlShiftSpace


#include "Character/TactCombCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATactCombCharacterBase::ATactCombCharacterBase()
{
	// 取消使用 Tick
	PrimaryActorTick.bCanEverTick = false;

	// 建立攝影機臂
	CharSprArm = CreateDefaultSubobject<USpringArmComponent>("CharSprArm");
	CharSprArm->SetupAttachment(RootComponent);

	// 建立攝影機(建立在攝影機臂上)
	CharCam = CreateDefaultSubobject<UCameraComponent>("CharCamera");
	CharCam->SetupAttachment(CharSprArm);
	
}

// Called when the game starts or when spawned
void ATactCombCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	
}

