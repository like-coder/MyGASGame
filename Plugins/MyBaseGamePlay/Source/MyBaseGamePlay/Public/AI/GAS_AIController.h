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
	// AI感知组件（用于感知敌人等）
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	// 视觉感知配置（用于设置视野范围、角度等）
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	TObjectPtr<UAISenseConfig_Sight> SightConfig;
};
