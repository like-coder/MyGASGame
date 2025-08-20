// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AN_SendGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagsManager.h"

void UAN_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp->GetOwner())
	{
		return;
	}

	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner());
	if (!OwnerASC)
	{
		return;
	}

	// ����һ��ָ��EventTag�Ŀ�Gameplay�¼���OwnerActor
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, FGameplayEventData());
}

FString UAN_SendGameplayEvent::GetNotifyName_Implementation() const
{
	// ��������������༭�������۵�
	// ��� EventTag �Ƿ���Ч
	if (EventTag.IsValid())
	{
		// �� GameplayTag ���Ϊ��� FName �㼶������ "Ability.Combo.Change.Combo02" �� ["Ability", "Combo", "Change", "Combo02"]��
		TArray<FName> TagNames;
		UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);

		// �������һ��������Ϊ֪ͨ���ƣ����� "Combo02"��
		return TagNames.Last().ToString();
	}
	return "None";
}
