// Copyright Gaia

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;// 武器

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttriburesEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttriburesEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttriburesEffect;

	virtual void InitAbilityActorInfo() {}
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> gameEffectClass, float level = 1.f) const;
	void InitializeDefaultAttributes() const;
public:	


};
