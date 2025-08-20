// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/GA_Combo.h"
#include "GAS/Core/TGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

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

		// 实现了接收到Tag事件的方法
		// 监听“连招切换”事件（如动画通知触发）
		UAbilityTask_WaitGameplayEvent* WaitComboChangeEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, TGameplayTags::Ability_Combo_Change, nullptr, false, false);
		WaitComboChangeEventTask->EventReceived.AddDynamic(this, &UGA_Combo::ComboChangedEventReceived);
		WaitComboChangeEventTask->ReadyForActivation();
	}
}

void UGA_Combo::ComboChangedEventReceived(FGameplayEventData Data)
{
	FGameplayTag EventTag = Data.EventTag;

	// 如果是结束连击标签传过来了就退出
	if (EventTag == TGameplayTags::Ability_Combo_Change_End)
	{
		NextComboName = NAME_None;
		UE_LOG(LogTemp, Log, TEXT("Combo End"))
			return;
	}

	// 获取下一个连段的名称
	TArray<FName> TagNames;
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);

	// Tag最后一段的名称比如Combo02,03,04等
	NextComboName = TagNames.Last();
	UE_LOG(LogTemp, Log, TEXT("Combo Changed to %s"), *NextComboName.ToString())
}
