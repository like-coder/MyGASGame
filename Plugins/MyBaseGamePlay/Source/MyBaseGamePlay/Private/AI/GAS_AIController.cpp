// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GAS_AIController.h"

AGAS_AIController::AGAS_AIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	// 配置视觉感知的关联检测设置：
	// - 检测敌人：启用
	// - 检测中立目标：禁用
	// - 检测友方单位：禁用
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	// 设置视觉感知参数：
	// - 视野半径
	SightConfig->SightRadius = 1000.f;
	// - 失去视野半径（当目标超出此范围时AI会认为失去目标）
	SightConfig->LoseSightRadius = 1200.f;
	// - 感知信息的最大保存时间：5秒,之后会遗忘该感知
	SightConfig->SetMaxAge(5.f);
	// - 周边视觉角度：180度
	SightConfig->PeripheralVisionAngleDegrees = 180.f;
	// 配置AI感知组件的视觉感知
	AIPerceptionComponent->ConfigureSense(*SightConfig);
}

void AGAS_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	// 随便设置的队伍
	SetGenericTeamId(0);
	IGenericTeamAgentInterface* PawnTeamInterface = Cast<IGenericTeamAgentInterface>(InPawn);
	if (PawnTeamInterface)
	{
		PawnTeamInterface->SetGenericTeamId(GetGenericTeamId());
	}
}
