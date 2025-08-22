// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/GA_Combo.h"
#include "GAS/Core/TGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"

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

		// ʵ���˽��յ�Tag�¼��ķ���
		// �����������л����¼����綯��֪ͨ������
		UAbilityTask_WaitGameplayEvent* WaitComboChangeEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, TGameplayTags::Ability_Combo_Change, nullptr, false, false);
		WaitComboChangeEventTask->EventReceived.AddDynamic(this, &UGA_Combo::ComboChangedEventReceived);
		WaitComboChangeEventTask->ReadyForActivation();		// ִ������
	}

	// ��ʼ����һ�����ж�����Ϊ��
	NextComboName = NAME_None;
	// ���ü���������루����������
	SetupWaitComboInputPress();
}

void UGA_Combo::ComboChangedEventReceived(FGameplayEventData Data)
{
	FGameplayTag EventTag = Data.EventTag;

	// ����ǽ���������ǩ�������˾��˳�
	if (EventTag == TGameplayTags::Ability_Combo_Change_End)
	{
		NextComboName = NAME_None;
		UE_LOG(LogTemp, Log, TEXT("Combo End"))
			return;
	}

	// ��ȡ��һ�����ε�����
	TArray<FName> TagNames;
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);

	// Tag���һ�ε����Ʊ���Combo02,03,04��
	NextComboName = TagNames.Last();
	UE_LOG(LogTemp, Log, TEXT("Combo Changed to %s"), *NextComboName.ToString())
}

void UGA_Combo::SetupWaitComboInputPress()
{
	// ����������������
	UAbilityTask_WaitInputPress* WaitInputPressTask = UAbilityTask_WaitInputPress::WaitInputPress(this);
	if (WaitInputPressTask)
	{
		// ��������Ӧ����
		WaitInputPressTask->OnPress.AddDynamic(this, &UGA_Combo::HandleInputPress);
		WaitInputPressTask->ReadyForActivation();		// ִ������
	}
}

void UGA_Combo::HandleInputPress(float TimeWaited)
{
	// �������ü�����������
	SetupWaitComboInputPress();
	// �����л�����һ�����ж�
	TryCommitCombo();
}

void UGA_Combo::TryCommitCombo()
{
	//û����һ��ֱ�ӷ���
	if (NextComboName == NAME_None)
	{
		return;
	}

	UAnimInstance* OwnerAnimInst = GetOwnerAnimInstance();
	if (OwnerAnimInst)
	{
		// ������̫���Զ��л�����һ��Ƭ�Σ����������Ч��
		OwnerAnimInst->Montage_SetNextSection(OwnerAnimInst->Montage_GetCurrentSection(ComboMontage), NextComboName, ComboMontage);
	}
}
