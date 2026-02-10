// Copyright Gaia


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
