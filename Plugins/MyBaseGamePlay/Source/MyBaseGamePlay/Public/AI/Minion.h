// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GAS_Character.h"
#include "Minion.generated.h"

/**
 * 小兵AI角色类，继承自ACCharacter
 * 负责小兵的队伍分配、激活状态、目标设置、皮肤切换等功能
 */
UCLASS()
class MYBASEGAMEPLAY_API AMinion : public AGAS_Character
{
	GENERATED_BODY()
public:
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	bool IsActive() const;
	void Activate();
	// 设置小兵的目标（如推进目标、攻击目标等）
	void SetGoal(AActor* Goal);

private:
	// 根据队伍ID切换小兵皮肤
	void PickSkinBaseOnTeamID();

	// 队伍ID同步时回调（用于网络同步后自动切换皮肤等）
	virtual void OnRep_TeamID() override;

	// 队伍ID到对应皮肤的映射表
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TMap<FGenericTeamId, TObjectPtr<USkeletalMesh>> SkinMap;

	// 黑板中用于存储目标的Key名
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName GoalBlackboardKeyName = "Goal";
};
