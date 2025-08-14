// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GAS_PlayerController.h"

void AGAS_PlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	GAS_PlayerCharacter = Cast<AGAS_PlayerCharacter>(NewPawn);
	if (GAS_PlayerCharacter)
	{
		GAS_PlayerCharacter->ServerSideInit();
	}
}

void AGAS_PlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	GAS_PlayerCharacter = Cast<AGAS_PlayerCharacter>(P);
	if (GAS_PlayerCharacter)
	{
		GAS_PlayerCharacter->ClientSideInit();
	}
}
