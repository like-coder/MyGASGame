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
	// ��֪��Ŀ��ʱ�Ļص�
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* TargetActor, FAIStimulus Stimulus);
	// ��ȡ��ǰ�ڰ��е�Ŀ�����
	const UObject* GetCurrentTarget() const;
	// ���õ�ǰĿ�굽�ڰ�
	void SetCurrentTarget(AActor* NewTarget);

	// ��֪Ŀ������ʱ�Ļص�
	UFUNCTION()
	void TargetForgotten(AActor* ForgottenActor);
	// ��ȡ��һ����֪���ĵ��ˣ�����Ŀ���л���
	AActor* GetNextPerceivedActor() const;
	// ���Ŀ���������������Ǹ�Ŀ�꣨�����֪���ݣ�
	void ForgetActorIfDead(AActor* ActorToForget);

private:
	// AI��֪��������ڸ�֪���˵ȣ�
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	// �Ӿ���֪���ã�����������Ұ��Χ���Ƕȵȣ�
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
	// ��Ϊ��ʵ��
	UPROPERTY(EditDefaultsOnly, Category = "AI Behavior")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	// �ڰ������ڴ洢Ŀ���Key��
	UPROPERTY(EditDefaultsOnly, Category = "AI Behavior")
	FName TargetBlackboardKeyName = "Target";
};
