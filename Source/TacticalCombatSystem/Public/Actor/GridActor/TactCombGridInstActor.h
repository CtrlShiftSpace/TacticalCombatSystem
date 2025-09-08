// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "Actor/GridActor/TactCombGridActorBase.h"
#include "TactCombGridInstActor.generated.h"

// 網格 Instance 參數設定
USTRUCT(BlueprintType)
struct FGridInstanceParam
{
	GENERATED_BODY()

	// 網格的中心位置
	UPROPERTY(EditDefaultsOnly)
	FVector CenterLocation = FVector::ZeroVector;

	// 網格大小
	UPROPERTY(EditDefaultsOnly)
	FVector GridSize = FVector(100.f, 100.f, 1.f);
	
	// 長邊的網格數量
	UPROPERTY(EditDefaultsOnly)
	int32 LengthGridNum = 5;

	// 寬邊的網格數量
	UPROPERTY(EditDefaultsOnly)
	int32 WidthGridNum = 4;
	
};

/**
 * 
 */
UCLASS()
class TACTICALCOMBATSYSTEM_API ATactCombGridInstActor : public ATactCombGridActorBase
{
	GENERATED_BODY()
	
public:
	ATactCombGridInstActor();
	
protected:
	virtual void BeginPlay() override;
	
	// 產生網格 Instance
	UFUNCTION(BlueprintCallable, Category = "GridInst Process")
	void SpawnGridInstance(const FGridInstanceParam& InGridInstParam);
	
	// 靜態 Instance 物件
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInstancedStaticMeshComponent> GridInstMesh;

	UPROPERTY(EditDefaultsOnly, Category = "GridInst Settings")
	FGridInstanceParam GridInstParam;
	
};
