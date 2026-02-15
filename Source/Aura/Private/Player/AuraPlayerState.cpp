// Copyright Gaia


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");// 内部此时已经关联AttributeSet
	AbilitySystemComponent->SetIsReplicated(true);// 可以被服务器复制到客户端
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	SetNetUpdateFrequency(100.f);// 服务器更新客户端频率
}
