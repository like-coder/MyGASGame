// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS_PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GAS_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API AGAS_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	// 玩家控制器控制一个Pawn时调用（该函数仅在服务器中调用）
	virtual void OnPossess(APawn* NewPawn) override;
	// 玩家控制器控制一个Pawn时调用（该函数仅在客户端中调用）
	virtual void AcknowledgePossession(APawn* P) override;

private:
	UPROPERTY()
	TObjectPtr<AGAS_PlayerCharacter> GAS_PlayerCharacter;
};
