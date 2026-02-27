// Copyright Gaia


#include "AbilitySystem/AuraAbilitySystemComponent.h"

UAuraAbilitySystemComponent::UAuraAbilitySystemComponent()
{

}

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* abilitySystemComponent, const FGameplayEffectSpec& effectSpec, FActiveGameplayEffectHandle activeHandlele)
{
	FGameplayTagContainer container;
	effectSpec.GetAllAssetTags(container);
	OnEffectAssetTagsDelegate.Broadcast(container);
}
