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
