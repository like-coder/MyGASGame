// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Core/GAS_GameplayAbility.h"
#include "GA_Combo.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API UGA_Combo : public UGAS_GameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	// Tag传入事件绑定
	UFUNCTION()
	void ComboChangedEventReceived(FGameplayEventData Data);

	/**
	 * @brief 设置监听连击输入按下的异步任务
	 *
	 * 该函数用于创建并初始化一个等待玩家按下连击输入的任务，
	 * 通常在连击能力激活时调用。
	 */
	void SetupWaitComboInputPress();

	/**
	 * @brief 处理连击输入按下的回调函数
	 *
	 * 当玩家按下连击输入时触发此函数，用于执行连击逻辑，
	 * 如切换到下一个连击阶段或播放下一段动画。
	 *
	 * @param TimeWaited 输入按下前的等待时间（秒）
	 */
	UFUNCTION()
	void HandleInputPress(float TimeWaited);

	/**
	 * @brief 尝试提交当前连击动作
	 *
	 * 该函数用于检查是否满足连击触发条件，并尝试激活下一个连击阶段。
	 * 若条件不满足，则可能重置连击状态或忽略此次输入。
	 */
	void TryCommitCombo();

	//处理接收伤害Tag的处理
	UFUNCTION()
	void DoDamage(FGameplayEventData Data);

	// 获取当前连击的伤害效果
	TSubclassOf<UGameplayEffect> GetDamageEffectForCurrentCombo() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> ComboMontage;

	// 存储下一段combo名称
	FName NextComboName;

	// 默认伤害效果类
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effect")
	TSubclassOf<UGameplayEffect> DefaultDamageEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effect")
	TMap<FName, TSubclassOf<UGameplayEffect>> DamageEffectMap;
};
