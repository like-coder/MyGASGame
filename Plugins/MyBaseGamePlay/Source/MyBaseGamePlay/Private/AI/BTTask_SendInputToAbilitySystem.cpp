// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_SendInputToAbilitySystem.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_SendInputToAbilitySystem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// ��ȡ��Ϊ�������AI������
	AAIController* OwnerAIC = OwnerComp.GetAIOwner();
	if (OwnerAIC)
	{
		// ��AI��������ȡ����Ƶ�Pawn������ϵͳ���
		UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerAIC->GetPawn());
		if (OwnerASC)
		{
			// ��������ϵͳ�����밴���¼�
			OwnerASC->PressInputID(static_cast<int32>(InputID));
			// ���밴�³ɹ�����������ִ�гɹ��Ľ��
			return EBTNodeResult::Succeeded;
		}
	}
	// δ�ҵ�AI������������ϵͳ�������������ִ��ʧ�ܵĽ��
	return EBTNodeResult::Failed;
}
