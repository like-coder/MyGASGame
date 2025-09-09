// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "GAS_AIController.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API AGAS_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AGAS_AIController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

private:
	// 感知到目标时的回调
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* TargetActor, FAIStimulus Stimulus);
	// 获取当前黑板中的目标对象
	const UObject* GetCurrentTarget() const;
	// 设置当前目标到黑板
	void SetCurrentTarget(AActor* NewTarget);

	// 感知目标遗忘时的回调
	UFUNCTION()
	void TargetForgotten(AActor* ForgottenActor);
	// 获取下一个感知到的敌人（用于目标切换）
	AActor* GetNextPerceivedActor() const;
	// 如果目标已死亡，则忘记该目标（清理感知数据）
	void ForgetActorIfDead(AActor* ActorToForget);

private:
	// AI感知组件（用于感知敌人等）
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	// 视觉感知配置（用于设置视野范围、角度等）
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
	// 行为树实例
	UPROPERTY(EditDefaultsOnly, Category = "AI Behavior")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	// 黑板中用于存储目标的Key名
	UPROPERTY(EditDefaultsOnly, Category = "AI Behavior")
	FName TargetBlackboardKeyName = "Target";
};
