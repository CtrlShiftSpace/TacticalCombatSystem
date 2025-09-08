// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GridClassInfo.generated.h"

// 網格形狀
UENUM(BlueprintType)
enum class EGridShape : uint8
{
	None,
	Triangle,
	Square,
	Hexagon
};

// 網格類型
USTRUCT()
struct FGridClassAssetInfo
{
	GENERATED_BODY()

	// 網格形狀的 Tag
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag GridShapeTag = FGameplayTag();

	// 網格大小
	UPROPERTY(EditDefaultsOnly)
	FVector MeshSize = FVector::ZeroVector;

	// 網格 Mesh 模型
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> GridMesh = nullptr;

	// 套用到網格 Mesh 的素材
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstance> GridMeshMaterial = nullptr;

	// 單一平面的網格 Mesh 模型
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> GridFlatMesh = nullptr;

	// 單一平面外框的素材
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstance> GridFlatBorderMaterial = nullptr;

	// 單一平面填充的素材
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialInstance> GridFlatFilledMaterial = nullptr;

};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TACTICALCOMBATSYSTEM_API UGridClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	// 根據網格形狀取得對應的素材資訊
	FGridClassAssetInfo GetGridClassAssetInfo(EGridShape GridShape) const;

private:

	// 網格形狀所對應的素材
	UPROPERTY(EditDefaultsOnly, Category = "Grid Class Settings")
	TMap<EGridShape, FGridClassAssetInfo> GridClassAssetInfoMap;
	

};
