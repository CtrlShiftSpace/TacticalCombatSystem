// Copyright  CtrlShiftSpace

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "TactCombCharacterBase.generated.h"

class UCharacterClassInfoBase;
enum class ECharacterClass : uint8;
class UAttributeSet;
class UAbilitySystemComponent;
class UGameplayEffect;
class UCameraComponent;
class USpringArmComponent;

UCLASS(Abstract)
class TACTICALCOMBATSYSTEM_API ATactCombCharacterBase : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	ATactCombCharacterBase();

	// 取得 ASC
	UAbilitySystemComponent* GetAbilitySystemComponent() const;

	/* Combat Interface */
	virtual int32 GetCharacterLevel_Implementation() override;
	/* end Combat Interface */

protected:
	virtual void BeginPlay() override;

	// 追蹤角色攝影彈簧臂
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CharSprArm;

	// 追蹤角色攝影機
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> CharCam;

	// 應用 GE 類別的效果給本身 Character 中的 ASC
	virtual void ApplyEffectClassToSelfAsc(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level = 1.f) const;
	
	// 初始化屬性值
	virtual void InitAttributes();

	// 初始化 Ability 相關的資訊
	virtual void InitAbilityActorInfo();

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	// 角色職業
	UPROPERTY(EditAnywhere, Category = "Character Class")
	ECharacterClass CharacterClass;

	// 角色職業資訊
	UPROPERTY(EditDefaultsOnly, Category = "Character Class")
	TObjectPtr<UCharacterClassInfoBase> CharacterClassInfo;
};
