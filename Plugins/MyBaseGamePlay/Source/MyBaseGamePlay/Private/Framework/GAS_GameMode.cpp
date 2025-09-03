// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/GAS_GameMode.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"

APlayerController* AGAS_GameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
    APlayerController* NewPlayerController = Super::SpawnPlayerController(InRemoteRole, Options);
    IGenericTeamAgentInterface* NewPlayerTeamInterface = Cast<IGenericTeamAgentInterface>(NewPlayerController);
    // ��ȡ�Ŷ�ID
    FGenericTeamId TeamId = GetTeamIDForPlayer(NewPlayerController);
    if (NewPlayerTeamInterface)
    {
        // �����Ŷ�ID
        NewPlayerTeamInterface->SetGenericTeamId(TeamId);
    }
    // ���������
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
    // �ڶ���������ǩӳ���в��Ҹö����Ӧ�ĳ������ǩ
    if (!TeamStartSpotTagMap.Contains(TeamID))
    {
        return nullptr;
    }

    // ���������е�����APlayerStart��Ա��Ѱ��ƥ���������
    for (TActorIterator<APlayerStart> it(GetWorld()); it; ++it)
    {
        if (it->PlayerStartTag == TeamStartSpotTagMap[TeamID])
        {
            // Taken��ʾ����������ռ��
            it->PlayerStartTag = FName("Taken");
            // �����ҵ���������
            return *it;
        }
    }
    // ���û���ҵ����ʵ������㣬����nullptr
    return nullptr;
}
