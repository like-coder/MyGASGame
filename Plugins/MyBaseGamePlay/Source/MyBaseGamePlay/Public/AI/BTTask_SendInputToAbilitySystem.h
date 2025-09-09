// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GAS/Core/GAS_GameplayAbilityTypes.h"
#include "BTTask_SendInputToAbilitySystem.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API UBTTask_SendInputToAbilitySystem : public UBTTaskNode
{
	GENERATED_BODY()

public:
	// ִ������
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Ability")
	ECAbilityInputID InputID;
};
