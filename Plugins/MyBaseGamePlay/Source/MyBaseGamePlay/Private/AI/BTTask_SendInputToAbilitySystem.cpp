// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_SendInputToAbilitySystem.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_SendInputToAbilitySystem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// 获取行为树组件的AI控制器
	AAIController* OwnerAIC = OwnerComp.GetAIOwner();
	if (OwnerAIC)
	{
		// 从AI控制器获取其控制的Pawn的能力系统组件
		UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerAIC->GetPawn());
		if (OwnerASC)
		{
			// 触发能力系统的输入按下事件
			OwnerASC->PressInputID(static_cast<int32>(InputID));
			// 输入按下成功，返回任务执行成功的结果
			return EBTNodeResult::Succeeded;
		}
	}
	// 未找到AI控制器或能力系统组件，返回任务执行失败的结果
	return EBTNodeResult::Failed;
}
