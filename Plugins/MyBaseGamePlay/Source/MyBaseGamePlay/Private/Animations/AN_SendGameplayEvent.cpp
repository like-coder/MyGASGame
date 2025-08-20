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

	// 发送一个指定EventTag的空Gameplay事件给OwnerActor
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, FGameplayEventData());
}

FString UAN_SendGameplayEvent::GetNotifyName_Implementation() const
{
	// 用来让这个动画编辑界面美观点
	// 检查 EventTag 是否有效
	if (EventTag.IsValid())
	{
		// 将 GameplayTag 拆分为多个 FName 层级（例如 "Ability.Combo.Change.Combo02" → ["Ability", "Combo", "Change", "Combo02"]）
		TArray<FName> TagNames;
		UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);

		// 返回最后一级名称作为通知名称（例如 "Combo02"）
		return TagNames.Last().ToString();
	}
	return "None";
}
