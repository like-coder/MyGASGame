// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/GameModeBase.h"
#include "GAS_GameMode.generated.h"

/**
 * 在游戏模式中管理队伍的分配
 */
UCLASS()
class MYBASEGAMEPLAY_API AGAS_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;

private:
	// 获取指定玩家的队伍ID
	FGenericTeamId GetTeamIDForPlayer(const AController* InController) const;
	// 根据队伍ID查找下一个出生点
	AActor* FindNextStartSpotForTeam(const FGenericTeamId& TeamID) const;

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	TMap<FGenericTeamId, FName> TeamStartSpotTagMap;
};
