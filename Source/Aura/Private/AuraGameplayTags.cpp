// Copyright Gaia


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"


void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), TEXT("减少伤害，提高格挡"));
}
