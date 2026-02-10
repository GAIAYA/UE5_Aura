// Copyright Gaia


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	USkeletalMeshComponent* mesh = GetMesh();
	if (mesh)
	{
		mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	}
}

void AAuraEnemy::HighlightActor()
{
	USkeletalMeshComponent* mesh = GetMesh();
	if (mesh)
	{
		mesh->SetRenderCustomDepth(true);
		mesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
	if (Weapon)
	{
		Weapon->SetRenderCustomDepth(true);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void AAuraEnemy::UnHighlightActor()
{
	USkeletalMeshComponent* mesh = GetMesh(); 
	if (mesh)
	{
		mesh->SetRenderCustomDepth(false);
	}
	if (Weapon)
	{
		Weapon->SetRenderCustomDepth(false);
	}
}
