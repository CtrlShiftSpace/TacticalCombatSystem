// Copyright  CtrlShiftSpace


#include "Character/TactCombCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystem/Data/CharacterClassInfoBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATactCombCharacterBase::ATactCombCharacterBase()
{
	// 取消使用 Tick
	PrimaryActorTick.bCanEverTick = false;
	
}

UAbilitySystemComponent* ATactCombCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ATactCombCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void ATactCombCharacterBase::ApplyEffectClassToSelfAsc(const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	// 先建立 FGameplayEffectContextHandle 類別並設定效果發動來源
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	// 透過傳入 FGameplayEffectContextHandle 產生 FGameplayEffectSpecHandle 類別，設定應用效果類型與對象
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ATactCombCharacterBase::InitAttributes()
{
	checkf(CharacterClassInfo, TEXT("CharacterClassInfo is not set"));
	// 取得該職業類別的資料
	const FCharacterClassDefaultInfo Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	// 設定屬性
	constexpr float InitLevel = 1.f;
	if (Info.PrimaryAttributes)
	{
		ApplyEffectClassToSelfAsc(Info.PrimaryAttributes, InitLevel);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s PrimaryAttributes is not set"), *GetName());
	}
	if (Info.SecondaryAttributes)
	{
		ApplyEffectClassToSelfAsc(Info.SecondaryAttributes, InitLevel);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s SecondaryAttributes is not set"), *GetName());
	}
	if (Info.VitalAttributes)
	{
		ApplyEffectClassToSelfAsc(Info.VitalAttributes, InitLevel);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s VitalAttributes is not set"), *GetName());
	}
}

void ATactCombCharacterBase::InitAbilityActorInfo()
{
}

