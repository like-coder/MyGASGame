// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GAS_AbilitySystemComponent.h"

void UGAS_AbilitySystemComponent::ApplyInitialEffects()
{
	// ��鵱ǰ����Ƿ�ӵ��ӵ���ߣ�����ӵ�����Ƿ��������Ȩ�ޣ�Ȩ���ԣ� 
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	for (const TSubclassOf<UGameplayEffect>& EffectClass : InitialEffects)
	{
		// ������ϷЧ�����������������ҪӦ�õ�Ч������������
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(EffectClass, 1, MakeEffectContext());
		// ����ϷЧ��Ӧ�õ�����
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void UGAS_AbilitySystemComponent::GiveInitialAbilities()
{
	// ��鵱ǰ����Ƿ�ӵ��ӵ���ߣ�����ӵ�����Ƿ��������Ȩ�ޣ�Ȩ���ԣ� 
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;

	for (const TSubclassOf<UGameplayAbility>& AbilityClass : BasicAbilities)
	{
		// ���輼�� �ȼ�Ϊ 1
		GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, -1, nullptr));
	}

	for (const TSubclassOf<UGameplayAbility>& AbilityClass : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityClass, 0, -1, nullptr));
	}
}
