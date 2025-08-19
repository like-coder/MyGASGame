// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/GA_Combo.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void UGA_Combo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!K2_CommitAbility())
	{
		K2_EndAbility();
		return;
	}

	// 服务器或预测端：播放Montage并监听动画和连招事件
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		// 蒙太奇任务代理
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ComboMontage);
		// 设置动画结束时的回调：当动画自然结束时结束技能
		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		// 设置动画被取消时的回调：当动画被手动取消时结束技能
		PlayComboMontageTask->OnCancelled.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		// 设置动画完成时的回调：当动画正常播放完成时结束技能
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		// 设置动画被中断时的回调：当动画被其他事件中断时结束技能
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		// 调用此函数激活任务，实际开始播放动画
		PlayComboMontageTask->ReadyForActivation();
	}
}
