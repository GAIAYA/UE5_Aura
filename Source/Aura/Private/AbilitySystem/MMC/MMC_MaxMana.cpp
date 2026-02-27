// Copyright Gaia


#include "AbilitySystem/MMC/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters evaluateParameters;
	evaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	evaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, evaluateParameters, intelligence);
	intelligence = FMath::Max<float>(intelligence, 0.f);

	ICombatInterface* combatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int level = combatInterface->GetAuraCharacterLevel();

	return 40.f + 1.5 * intelligence + 5 * level;
}
