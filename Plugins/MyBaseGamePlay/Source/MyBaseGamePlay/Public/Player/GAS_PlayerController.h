// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS_PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Base/GameplayWidget.h"
#include "GenericTeamAgentInterface.h"
#include "GAS_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API AGAS_PlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	// 玩家控制器控制一个Pawn时调用（该函数仅在服务器中调用）
	virtual void OnPossess(APawn* NewPawn) override;
	// 玩家控制器控制一个Pawn时调用（该函数仅在客户端中调用）
	virtual void AcknowledgePossession(APawn* P) override;

	// 设置团队ID
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	// 获取团队ID
	virtual FGenericTeamId GetGenericTeamId() const override;
	// 判断当前对象对另一个对象的态度
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void SpawnGameplayWidget();
	void SetAndBoundToGameplayAttributes();

private:
	UPROPERTY()
	TObjectPtr<AGAS_PlayerCharacter> GAS_PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGameplayWidget> GameplayWidgetClass;

	UPROPERTY()
	TObjectPtr<UGameplayWidget> GameplayWidget;

	// 团队ID
	UPROPERTY(Replicated)
	FGenericTeamId TeamID;
};
