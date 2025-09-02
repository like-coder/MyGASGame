// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GAS_PlayerController.h"
#include "GAS/GAS_AttributeSet.h"
#include "Net/UnrealNetwork.h"

void AGAS_PlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	GAS_PlayerCharacter = Cast<AGAS_PlayerCharacter>(NewPawn);
	if (GAS_PlayerCharacter)
	{
		GAS_PlayerCharacter->ServerSideInit();
		GAS_PlayerCharacter->SetGenericTeamId(TeamID);
	}
}

void AGAS_PlayerController::AcknowledgePossession(APawn* P)
{
	//�ú�����BeginPlay�������
	Super::AcknowledgePossession(P);
	GAS_PlayerCharacter = Cast<AGAS_PlayerCharacter>(P);
	if (GAS_PlayerCharacter)
	{
		GAS_PlayerCharacter->ClientSideInit();
		//����UI
		SpawnGameplayWidget();
	}
}

void AGAS_PlayerController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamID = NewTeamID;
}

FGenericTeamId AGAS_PlayerController::GetGenericTeamId() const
{
	return TeamID;
}

void AGAS_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//���Ŷ�ID���Ը��Ƶ����еĿͻ���
	DOREPLIFETIME(AGAS_PlayerController, TeamID);
}

void AGAS_PlayerController::SetAndBoundToGameplayAttributes()
{
	UAbilitySystemComponent* AbilitySystemComponent = GAS_PlayerCharacter->GetAbilitySystemComponent();
	if (AbilitySystemComponent)
	{
		GameplayWidget->GetHealthBar()->SetAndBoundToGameplayAttribute(AbilitySystemComponent, UGAS_AttributeSet::GetHealthAttribute(), UGAS_AttributeSet::GetMaxHealthAttribute());
		GameplayWidget->GetManaBar()->SetAndBoundToGameplayAttribute(AbilitySystemComponent, UGAS_AttributeSet::GetManaAttribute(), UGAS_AttributeSet::GetMaxManaAttribute());
	}
}

void AGAS_PlayerController::SpawnGameplayWidget()
{
	// ��鵱ǰ��ҿ������Ƿ��Ǳ�����ҿ�����
	if (!IsLocalPlayerController()) return;

	if (GameplayWidgetClass)
	{
		GameplayWidget = CreateWidget<UGameplayWidget>(this, GameplayWidgetClass);
		if (GameplayWidget)
		{
			// ��ӵ��ӿ���
			GameplayWidget->AddToViewport();
			SetAndBoundToGameplayAttributes();
		}
	}
}
