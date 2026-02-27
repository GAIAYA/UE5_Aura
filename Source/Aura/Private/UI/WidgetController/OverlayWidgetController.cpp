// Copyright Gaia


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* auraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(auraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(auraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(auraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(auraAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* auraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		auraAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		auraAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		auraAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		auraAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
		);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->OnEffectAssetTagsDelegate.AddLambda(
		[this](const FGameplayTagContainer& assetTags)->void
		{
			FGameplayTag messageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			for (const auto& tag : assetTags)
			{
				if (tag.MatchesTag(messageTag))
				{
					if (FUIWidgetRow* row = GetTableRowByTags<FUIWidgetRow>(MessageWidgetDataTable.Get(), tag))
						MessageWidgetRowDelegate.Broadcast(*row);
				}
			}
		}
	);
}
