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
	// ��ҿ���������һ��Pawnʱ���ã��ú������ڷ������е��ã�
	virtual void OnPossess(APawn* NewPawn) override;
	// ��ҿ���������һ��Pawnʱ���ã��ú������ڿͻ����е��ã�
	virtual void AcknowledgePossession(APawn* P) override;

private:
	UPROPERTY()
	TObjectPtr<AGAS_PlayerCharacter> GAS_PlayerCharacter;
};
