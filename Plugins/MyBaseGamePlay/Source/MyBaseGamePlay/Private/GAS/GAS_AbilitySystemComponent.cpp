// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GAS_AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UGAS_AbilitySystemComponent::UGAS_AbilitySystemComponent()
{
	//注册以接收生命值变化的通知
	GetGameplayAttributeValueChangeDelegate(UGAS_AttributeSet::GetHealthAttribute()).AddUObject(this, &UGAS_AbilitySystemComponent::HealthUpdated);
}

void UGAS_AbilitySystemComponent::ApplyInitialEffects()
{
	// 检查当前组件是否拥有拥有者，并且拥有者是否具有网络权限（权威性） 
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		// 创建游戏效果规格句柄，用于描述要应用的效果及其上下文
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(EffectClass, 1, MakeEffectContext());
		// 将游戏效果应用到自身
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void UGAS_AbilitySystemComponent::GiveInitialAbilities()
{
	// 检查当前组件是否拥有拥有者，并且拥有者是否具有网络权限（权威性） 
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	for (const TPair<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : BasicAbilities)
	{
		// 赋予技能 等级为 1
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 1, static_cast<int32>(AbilityPair.Key), nullptr));
	}

	for (const TPair<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 0, static_cast<int32>(AbilityPair.Key), nullptr));
	}
}

void UGAS_AbilitySystemComponent::AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(GameplayEffect, Level, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void UGAS_AbilitySystemComponent::HealthUpdated(const FOnAttributeChangeData& ChangeData)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	// 角色死亡
	if (ChangeData.NewValue <= 0.0f && DeathEffect)
	{
		AuthApplyGameplayEffect(DeathEffect);
	}
}

void UGAS_AbilitySystemComponent::ApplyFullStatEffect()
{
	AuthApplyGameplayEffect(FullStatEffect);
}
