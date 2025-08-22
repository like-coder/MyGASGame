// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Core/GAS_GameplayAbilityTypes.h"
#include "GAS_AbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API UGAS_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	// ��ʼЧ��
	void ApplyInitialEffects();
	// ���ܳ�ʼ��
	void GiveInitialAbilities();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	// ��������
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> BasicAbilities;

	// ����
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> Abilities;

};
