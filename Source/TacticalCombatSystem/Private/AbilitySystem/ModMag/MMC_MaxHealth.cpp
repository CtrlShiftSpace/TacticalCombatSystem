// Copyright  CtrlShiftSpace


#include "AbilitySystem/ModMag/MMC_MaxHealth.h"

#include "AbilitySystem/TactCombAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	// 設定指定的屬性
	VigorDef.AttributeToCapture = UTactCombAttributeSet::GetVigorAttribute();
	// 為施加到目標身上效果
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	// true: 當 Gameplay Effect Spec 創建執行
	// false: 當 Gameplay Effect 真正被應用才執行
	VigorDef.bSnapshot = false;

	// 添加到列表中才能夠取得屬性值
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// 從 Source 與 Target 取得 Tag
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// 取得目前的Vigor值
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	// 透過 ICombatInterface 介面的方法，取得等級
	int32 CharacterLevel = 1;
	// 確認是否有實作 CombatInterface，注意這邊在 Implements 是使用 UCombatInterface
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		CharacterLevel = ICombatInterface::Execute_GetCharacterLevel(Spec.GetContext().GetSourceObject());
	}

	// 將Vigor值與等級進行計算
	return 80.f + 2.5f * Vigor + 10.f * CharacterLevel;
}
