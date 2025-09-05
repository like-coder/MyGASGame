// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
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

private:
	// AI��֪��������ڸ�֪���˵ȣ�
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	// �Ӿ���֪���ã�����������Ұ��Χ���Ƕȵȣ�
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
};
