// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/GameModeBase.h"
#include "GAS_GameMode.generated.h"

/**
 * ����Ϸģʽ�й������ķ���
 */
UCLASS()
class MYBASEGAMEPLAY_API AGAS_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;

private:
	// ��ȡָ����ҵĶ���ID
	FGenericTeamId GetTeamIDForPlayer(const AController* InController) const;
	// ���ݶ���ID������һ��������
	AActor* FindNextStartSpotForTeam(const FGenericTeamId& TeamID) const;

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	TMap<FGenericTeamId, FName> TeamStartSpotTagMap;
};
