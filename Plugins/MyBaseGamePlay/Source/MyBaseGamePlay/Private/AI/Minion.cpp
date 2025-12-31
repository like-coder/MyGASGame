// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Minion.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void AMinion::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
	PickSkinBaseOnTeamID();
}

bool AMinion::IsActive() const
{
	return !IsDead();
}

void AMinion::Activate()
{
	// “∆≥˝À¿Õˆ±Í«©£¨∏¥ªÓ
	RespawnImmediately();
}

void AMinion::SetGoal(AActor* Goal)
{
	AAIController* AIController = GetController<AAIController>();
	if (AIController)
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();
		if (BlackboardComponent)
		{
			BlackboardComponent->SetValueAsObject(GoalBlackboardKeyName, Goal);
		}
	}
}

void AMinion::PickSkinBaseOnTeamID()
{
	FGenericTeamId Skin_TeamId = GetGenericTeamId();
	if (SkinMap.Contains(Skin_TeamId))
	{
		GetMesh()->SetSkeletalMesh(SkinMap[Skin_TeamId].Get());
	}
}

void AMinion::OnRep_TeamID()
{
	PickSkinBaseOnTeamID();
}
