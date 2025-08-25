// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_AttackWindow.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API UANS_AttackWindow : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
private:
	// ��������GameplayCue���粥��������Ч����Ч�ȣ�
	void SendLocalGameplayCue(const FHitResult& HitResult) const;

private:
	// ������GameplayCue��ǩ����������Ч����Ч�ȣ�
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	FGameplayTagContainer TriggerGameplayCueTags;

	// Ŀ����Ӫ���ˣ���ֻ�������ˣ�
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability", meta = (DisplayName = "Ŀ����Ӫ"))
	TEnumAsByte<ETeamAttitude::Type> TargetTeam = ETeamAttitude::Hostile;

	// ���μ��뾶
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability", meta = (DisplayName = "����뾶"))
	float SphereSweepRadius = 60.f;

	// �Ƿ���Ƶ��Թ켣
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability", meta = (DisplayName = "���Ƶ��Թ켣"))
	bool bDrawDebug = true;

	// �Ƿ�����Լ�
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability", meta = (DisplayName = "��������"))
	bool bIgnoreOwner = true;

	// �Ƿ�ʹ������,��һ�����浶��
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability", meta = (DisplayName = "ʹ������"))
	bool bUseWeapon = false;

	// ���͵�Tag
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	FGameplayTag EventTag;

	// ��������
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	TArray<FName> TargetSocketNames;

	/*�������*/
	// ��¼��ײ��ǰһ֡��λ��
	TArray<FVector> Locations;
	// ���ߵ�Set�ƺ��е�֣����ԣ�`������`�����е����ø���
	// ��ײ���� Actor
	TArray<TWeakObjectPtr<AActor>> HitActors;

	// �������õ������������ýӿڴ�������castҲ����
	// ��ǰ����������, �Ҳ���һֱ������������Ľӿ�
	mutable TWeakObjectPtr<USkeletalMeshComponent> AttackMesh;

	// ���ݴ����õ�
	mutable TWeakInterfacePtr<IGenericTeamAgentInterface> OwnerTeamInterface;
};
