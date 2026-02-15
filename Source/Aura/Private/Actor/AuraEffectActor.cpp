// Copyright Gaia


#include "Actor/AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* overLappedComponent, AActor* otherActor,
	UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (IAbilitySystemInterface* aSCInterface = Cast<IAbilitySystemInterface>(otherActor))
	{
		const UAuraAttributeSet* attributeSet = Cast<UAuraAttributeSet>(aSCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		UAuraAttributeSet* mutablAttributeSet = const_cast<UAuraAttributeSet*>(attributeSet);
		mutablAttributeSet->SetHealth(attributeSet->GetHealth() + 25.f);
		mutablAttributeSet->SetMana(attributeSet->GetMana() - 5.f);
		Destroy();
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, 
	UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{

}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}


