// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/GridClassInfo.h"
#include "GameFramework/Actor.h"
#include "TactCombGridActor.generated.h"

enum class EGridShape : uint8;

UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombGridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATactCombGridActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 呈現網格形狀
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grid Class Info")
	EGridShape GridShape = EGridShape::Square;

	// 網格類型資訊
	UPROPERTY()
	TObjectPtr<UGridClassInfo> GridClassInfo;

	// 靜態物件
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> GridMesh;
};
