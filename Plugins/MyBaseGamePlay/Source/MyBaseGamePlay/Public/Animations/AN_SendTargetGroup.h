// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SendTargetGroup.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API UAN_SendTargetGroup : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	// ���μ��뾶
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	float SphereSweepRadius = 60.f;

	// �Ƿ���Ƶ��Թ켣
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	bool bDrawDebug = true;

	// �Ƿ�����Լ�
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	bool bIgnoreOwner = true;

	// ���͵�Tag
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	FGameplayTag EventTag;

	// ��������
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	TArray<FName> TargetSocketNames;
};
