// Copyright  CtrlShiftSpace


#include "Player/TacticalCombatPlayerController.h"

ATacticalCombatPlayerController::ATacticalCombatPlayerController()
{
	bReplicates = true;
}

void ATacticalCombatPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 顯示滑鼠游標
	bShowMouseCursor = true;
	// 設定預設滑鼠游標
	DefaultMouseCursor = EMouseCursor::Default;
}
