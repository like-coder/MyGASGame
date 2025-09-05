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
