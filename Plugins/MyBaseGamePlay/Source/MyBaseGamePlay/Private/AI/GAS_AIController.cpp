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
	// 感知目标更新
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AGAS_AIController::TargetPerceptionUpdated);
	// 感知目标遗忘
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &AGAS_AIController::TargetForgotten);
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
	// 检查是否成功感知到目标
	if (Stimulus.WasSuccessfullySensed())
	{
		// 如果当前没有目标，则设置当前目标为感知到的目标
		if (!GetCurrentTarget())
		{
			SetCurrentTarget(TargetActor);
		}
	}
	else
	{
		//// 如果当前目标是感知到的目标，但感知不成功，则清除当前目标
		//if (GetCurrentTarget() == TargetActor)
		//{
		//	SetCurrentTarget(nullptr);
		//}
	}
}

const UObject* AGAS_AIController::GetCurrentTarget() const
{
	// 获取黑板组件
	const UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (BlackboardComponent)
	{
		// 从黑板组件中根据键名获取目标对象
		return BlackboardComponent->GetValueAsObject(TargetBlackboardKeyName);
	}
	// 如果黑板组件不存在，返回nullptr
	return nullptr;
}

void AGAS_AIController::SetCurrentTarget(AActor* NewTarget)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	// 如果黑板组件为空，则不执行任何操作
	if (!BlackboardComponent)
	{
		return;
	}

	if (NewTarget)
	{
		// 如果新目标不为空，则在黑板上设置新目标
		BlackboardComponent->SetValueAsObject(TargetBlackboardKeyName, NewTarget);
	}
	else
	{
		// 如果新目标为空，则从黑板上清除当前目标
		BlackboardComponent->ClearValue(TargetBlackboardKeyName);
	}
}

void AGAS_AIController::TargetForgotten(AActor* ForgottenActor)
{
	if (!ForgottenActor)
	{
		return;
	}

	// 如果丢失的是当前的目标，则切换到下一个感知到的目标
	if (GetCurrentTarget() == ForgottenActor)
	{
		SetCurrentTarget(GetNextPerceivedActor());
	}
}

AActor* AGAS_AIController::GetNextPerceivedActor() const
{
	if (PerceptionComponent)
	{
		// 存储感知到的Actor
		TArray<AActor*> Actors;
		// 获取感知到的敌对Actor并存储到数组中
		AIPerceptionComponent->GetPerceivedHostileActors(Actors);
		// 如果敌对Actor的数量不为零
		if (!Actors.IsEmpty())
		{
			// 返回第一个
			return Actors[0];
		}
	}
	return nullptr;
}
