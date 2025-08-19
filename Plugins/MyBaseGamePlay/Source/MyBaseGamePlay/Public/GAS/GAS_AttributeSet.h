// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GAS_AttributeSet.generated.h"

//宏的设置，编译时会默认给变量生成相应的Getter以及Setter函数，当前设置会生成四个函数，获取属性，获取值，设置值，以及初始化值。
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
	// 用于声明哪些属性需要在网络中进行复制
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
	// 当Attribute的CurrentValue被改变之前调用
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	// 仅在instant Gameplay Effect使Attribute的BaseValue改变时触发
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
