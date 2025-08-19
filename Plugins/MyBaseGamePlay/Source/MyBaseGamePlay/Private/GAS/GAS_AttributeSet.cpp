// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GAS_AttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

void UGAS_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UGAS_AttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// 记得要调用父类的执行。
	Super::PreAttributeChange(Attribute, NewValue);
	//CurrentValue值的限定
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UGAS_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// 记得要调用父类的执行。
	Super::PostGameplayEffectExecute(Data);
	//BaseValue值的限定
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0, GetMaxMana()));
	}
}

void UGAS_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	//用于处理将由客户端进行预测性修改的属性
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Health, OldHealth);
}

void UGAS_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, MaxHealth, OldMaxHealth);
}

void UGAS_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Mana, OldMana);
}

void UGAS_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, MaxMana, OldMaxMana);
}
