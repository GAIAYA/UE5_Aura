// Copyright Gaia


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystemComponent.h"
#include "UI/HUD/AuraHUD.h"
#include "Player/AuraPlayerController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraCharacter::AAuraCharacter()
{
	
	UCharacterMovementComponent* characterMovement = GetCharacterMovement();
	check(characterMovement);
	characterMovement->bOrientRotationToMovement = true;// 角色方向朝向移动方向
	characterMovement->RotationRate = FRotator(0.f, 400.f, 0.f);
	characterMovement->bConstrainToPlane = true;
	characterMovement->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// 为服务器初始化AbilityActorInfo
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// 为客户端初始化AbilityActorInfo
	InitAbilityActorInfo();
}

int32 AAuraCharacter::GetAuraCharacterLevel()
{
	AAuraPlayerState* playState = GetPlayerState<AAuraPlayerState>();
	check(playState);
	return playState->GetAuraCharacterLevel();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* playState = GetPlayerState<AAuraPlayerState>();
	check(playState);
	playState->GetAbilitySystemComponent()->InitAbilityActorInfo(playState, this);
	Cast<UAuraAbilitySystemComponent>(playState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = playState->GetAbilitySystemComponent();
	AttributeSet = playState->GetAttributeSet();


	// 初始化Overlay控件和对应的WidgetController
	if (AAuraPlayerController* pc = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* auraHUD = Cast<AAuraHUD>(pc->GetHUD()))
			auraHUD->InitOverlay(pc, playState, AbilitySystemComponent, AttributeSet);
	}
	InitializeDefaultAttributes();
}


