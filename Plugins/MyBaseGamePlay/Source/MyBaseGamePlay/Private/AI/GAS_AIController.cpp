// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GAS_AIController.h"

AGAS_AIController::AGAS_AIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	// �����Ӿ���֪�Ĺ���������ã�
	// - �����ˣ�����
	// - �������Ŀ�꣺����
	// - ����ѷ���λ������
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	// �����Ӿ���֪������
	// - ��Ұ�뾶
	SightConfig->SightRadius = 1000.f;
	// - ʧȥ��Ұ�뾶����Ŀ�곬���˷�ΧʱAI����ΪʧȥĿ�꣩
	SightConfig->LoseSightRadius = 1200.f;
	// - ��֪��Ϣ����󱣴�ʱ�䣺5��,֮��������ø�֪
	SightConfig->SetMaxAge(5.f);
	// - �ܱ��Ӿ��Ƕȣ�180��
	SightConfig->PeripheralVisionAngleDegrees = 180.f;
	// ����AI��֪������Ӿ���֪
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	// ��֪Ŀ�����
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AGAS_AIController::TargetPerceptionUpdated);
	// ��֪Ŀ������
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &AGAS_AIController::TargetForgotten);
}

void AGAS_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// ������õĶ���
	SetGenericTeamId(0);
	IGenericTeamAgentInterface* PawnTeamInterface = Cast<IGenericTeamAgentInterface>(InPawn);
	if (PawnTeamInterface)
	{
		PawnTeamInterface->SetGenericTeamId(GetGenericTeamId());
	}
}

void AGAS_AIController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AGAS_AIController::TargetPerceptionUpdated(AActor* TargetActor, FAIStimulus Stimulus)
{
	// ����Ƿ�ɹ���֪��Ŀ��
	if (Stimulus.WasSuccessfullySensed())
	{
		// �����ǰû��Ŀ�꣬�����õ�ǰĿ��Ϊ��֪����Ŀ��
		if (!GetCurrentTarget())
		{
			SetCurrentTarget(TargetActor);
		}
	}
	else
	{
		//// �����ǰĿ���Ǹ�֪����Ŀ�꣬����֪���ɹ����������ǰĿ��
		//if (GetCurrentTarget() == TargetActor)
		//{
		//	SetCurrentTarget(nullptr);
		//}
	}
}

const UObject* AGAS_AIController::GetCurrentTarget() const
{
	// ��ȡ�ڰ����
	const UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (BlackboardComponent)
	{
		// �Ӻڰ�����и��ݼ�����ȡĿ�����
		return BlackboardComponent->GetValueAsObject(TargetBlackboardKeyName);
	}
	// ����ڰ���������ڣ�����nullptr
	return nullptr;
}

void AGAS_AIController::SetCurrentTarget(AActor* NewTarget)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	// ����ڰ����Ϊ�գ���ִ���κβ���
	if (!BlackboardComponent)
	{
		return;
	}

	if (NewTarget)
	{
		// �����Ŀ�겻Ϊ�գ����ںڰ���������Ŀ��
		BlackboardComponent->SetValueAsObject(TargetBlackboardKeyName, NewTarget);
	}
	else
	{
		// �����Ŀ��Ϊ�գ���Ӻڰ��������ǰĿ��
		BlackboardComponent->ClearValue(TargetBlackboardKeyName);
	}
}

void AGAS_AIController::TargetForgotten(AActor* ForgottenActor)
{
	if (!ForgottenActor)
	{
		return;
	}

	// �����ʧ���ǵ�ǰ��Ŀ�꣬���л�����һ����֪����Ŀ��
	if (GetCurrentTarget() == ForgottenActor)
	{
		SetCurrentTarget(GetNextPerceivedActor());
	}
}

AActor* AGAS_AIController::GetNextPerceivedActor() const
{
	if (PerceptionComponent)
	{
		// �洢��֪����Actor
		TArray<AActor*> Actors;
		// ��ȡ��֪���ĵж�Actor���洢��������
		AIPerceptionComponent->GetPerceivedHostileActors(Actors);
		// ����ж�Actor��������Ϊ��
		if (!Actors.IsEmpty())
		{
			// ���ص�һ��
			return Actors[0];
		}
	}
	return nullptr;
}
