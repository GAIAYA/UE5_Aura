// Copyright Gaia


#include "AbilitySystem/MMC/MMC_MaxHealth.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	FAggregatorEvaluateParameters evaluationParameters;
	evaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	evaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, evaluationParameters, vigor);
	vigor = FMath::Max<float>(vigor, 0.f);

	ICombatInterface* combatInterface = Cast<ICombatInterface>(Spec.GetEffectContext().GetSourceObject());
	int level = combatInterface->GetAuraCharacterLevel();

	return 80.f + 2.5 * vigor + 10.f * level;
}
