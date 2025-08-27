// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GAS/GAS_AttributeSet.h"
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
	UGAS_AbilitySystemComponent();
	// 初始效果
	void ApplyInitialEffects();
	// 技能初始化
	void GiveInitialAbilities();
	// 服务端添加GE
	void AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level = 1);

private:
	void HealthUpdated(const FOnAttributeChangeData& ChangeData);
	// 回满血、满蓝效果
	void ApplyFullStatEffect();

private:
	// 初始化属性效果
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

	// 死亡效果
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> DeathEffect;

	// 满血、满蓝效果
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> FullStatEffect;

	// 基础技能
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> BasicAbilities;

	// 技能
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Ability")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> Abilities;

};
