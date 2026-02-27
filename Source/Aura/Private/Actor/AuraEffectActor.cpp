// Copyright Gaia


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
//#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "ActiveGameplayEffectHandle.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraEffectActor::ApplyEffectToTarget(AActor* targetActor, TSubclassOf<UGameplayEffect> gameplayEffectClass)
{
	if (UAbilitySystemComponent* targetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetActor))
	{
		check(gameplayEffectClass);
		FGameplayEffectContextHandle context = targetASC->MakeEffectContext();
		context.AddSourceObject(this);
		FGameplayEffectSpecHandle effectspec = targetASC->MakeOutgoingSpec(gameplayEffectClass, ActorLevel, context);
		FActiveGameplayEffectHandle activeHandle = targetASC->ApplyGameplayEffectSpecToSelf(*(effectspec.Data.Get()));
		if (effectspec.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			ActiveEffectsHandlesMap.Add(activeHandle, targetASC);
		}
	}
}

void AAuraEffectActor::RemoveEffectToTarget(AActor* targetActor)
{
	UAbilitySystemComponent* targetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(targetActor);
	if (!IsValid(targetASC)) return;

	TArray<FActiveGameplayEffectHandle> waitRemoveHandlesArray;
	for (auto& pair : ActiveEffectsHandlesMap)
	{
		if (pair.Value == targetASC)
		{
			targetASC->RemoveActiveGameplayEffect(pair.Key, 1);
			waitRemoveHandlesArray.Add(pair.Key);
		}
	}
	for (auto& handle : waitRemoveHandlesArray)
	{
		ActiveEffectsHandlesMap.Remove(handle);
	}
	if (bDestoryActorOnEffectRemoval)
	{
		Destroy();
	}
}

void AAuraEffectActor::OnOverlap(AActor* targetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(targetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(targetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(targetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* targetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(targetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(targetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(targetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		RemoveEffectToTarget(targetActor);
	}
}


