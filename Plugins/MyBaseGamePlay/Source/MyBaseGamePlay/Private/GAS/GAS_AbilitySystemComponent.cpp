// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GAS_AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UGAS_AbilitySystemComponent::UGAS_AbilitySystemComponent()
{
	//ע���Խ�������ֵ�仯��֪ͨ
	GetGameplayAttributeValueChangeDelegate(UGAS_AttributeSet::GetHealthAttribute()).AddUObject(this, &UGAS_AbilitySystemComponent::HealthUpdated);
}

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

	for (const TPair<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : BasicAbilities)
	{
		// ���輼�� �ȼ�Ϊ 1
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

	// ��ɫ����
	if (ChangeData.NewValue <= 0.0f && DeathEffect)
	{
		AuthApplyGameplayEffect(DeathEffect);
	}
}

void UGAS_AbilitySystemComponent::ApplyFullStatEffect()
{
	AuthApplyGameplayEffect(FullStatEffect);
}
