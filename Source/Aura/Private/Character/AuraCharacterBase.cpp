// Copyright Gaia


#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> gameEffectClass, float level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(gameEffectClass);
	FGameplayEffectContextHandle contextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	contextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle effectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(gameEffectClass, level, contextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*effectSpecHandle.Data.Get());
}

void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttriburesEffect);
	ApplyEffectToSelf(DefaultSecondaryAttriburesEffect);
	ApplyEffectToSelf(DefaultVitalAttriburesEffect);
}

