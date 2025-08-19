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

	// ��������Ԥ��ˣ�����Montage�����������������¼�
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		// ��̫���������
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ComboMontage);
		// ���ö�������ʱ�Ļص�����������Ȼ����ʱ��������
		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		// ���ö�����ȡ��ʱ�Ļص������������ֶ�ȡ��ʱ��������
		PlayComboMontageTask->OnCancelled.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		// ���ö������ʱ�Ļص��������������������ʱ��������
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		// ���ö������ж�ʱ�Ļص����������������¼��ж�ʱ��������
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &UGA_Combo::K2_EndAbility);
		// ���ô˺�����������ʵ�ʿ�ʼ���Ŷ���
		PlayComboMontageTask->ReadyForActivation();
	}
}
