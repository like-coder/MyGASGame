// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GAS_GameMode.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"

APlayerController* AGAS_GameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
    APlayerController* NewPlayerController = Super::SpawnPlayerController(InRemoteRole, Options);
    IGenericTeamAgentInterface* NewPlayerTeamInterface = Cast<IGenericTeamAgentInterface>(NewPlayerController);
    // 获取团队ID
    FGenericTeamId TeamId = GetTeamIDForPlayer(NewPlayerController);
    if (NewPlayerTeamInterface)
    {
        // 设置团队ID
        NewPlayerTeamInterface->SetGenericTeamId(TeamId);
    }
    // 分配出生点
    NewPlayerController->StartSpot = FindNextStartSpotForTeam(TeamId);
    return NewPlayerController;
}

FGenericTeamId AGAS_GameMode::GetTeamIDForPlayer(const AController* InController) const
{
    static int PlayerCount = 0;
    ++PlayerCount;
    return FGenericTeamId(PlayerCount % 2);
}

AActor* AGAS_GameMode::FindNextStartSpotForTeam(const FGenericTeamId& TeamID) const
{
    // 在队伍出生点标签映射中查找该队伍对应的出生点标签
    if (!TeamStartSpotTagMap.Contains(TeamID))
    {
        return nullptr;
    }

    // 遍历世界中的所有APlayerStart演员，寻找匹配的重生点
    for (TActorIterator<APlayerStart> it(GetWorld()); it; ++it)
    {
        if (it->PlayerStartTag == TeamStartSpotTagMap[TeamID])
        {
            // Taken表示将重生点标记占用
            it->PlayerStartTag = FName("Taken");
            // 返回找到的重生点
            return *it;
        }
    }
    // 如果没有找到合适的重生点，返回nullptr
    return nullptr;
}
