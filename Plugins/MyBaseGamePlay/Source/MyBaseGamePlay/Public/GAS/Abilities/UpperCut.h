// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Core/GAS_GameplayAbility.h"
#include "UpperCut.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API UUpperCut : public UGAS_GameplayAbility
{
	GENERATED_BODY()
public:
	//激活技能时调用
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	// 上勾拳动画Montage
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> UpperCutMontage;

	// 启动击飞效果
	UFUNCTION()
	void StartLaunching(FGameplayEventData EventData);
};
