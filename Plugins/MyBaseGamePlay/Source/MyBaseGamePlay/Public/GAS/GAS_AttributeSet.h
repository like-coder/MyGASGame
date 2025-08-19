// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GAS_AttributeSet.generated.h"

//������ã�����ʱ��Ĭ�ϸ�����������Ӧ��Getter�Լ�Setter��������ǰ���û������ĸ���������ȡ���ԣ���ȡֵ������ֵ���Լ���ʼ��ֵ��
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API UGAS_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	// ����������Щ������Ҫ�������н��и���
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
	// ��Attribute��CurrentValue���ı�֮ǰ����
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	// ����instant Gameplay EffectʹAttribute��BaseValue�ı�ʱ����
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);

public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;					
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;				
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;					
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;					
	ATTRIBUTE_ACCESSORS(UGAS_AttributeSet, MaxMana)
};
