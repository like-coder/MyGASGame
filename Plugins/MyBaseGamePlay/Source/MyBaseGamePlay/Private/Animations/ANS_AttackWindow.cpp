// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/ANS_AttackWindow.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameplayEffectTypes.h"



void UANS_AttackWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp) return;

	// ��ʼ��
	Locations.SetNum(TargetSocketNames.Num());
	// ���������
	if (bUseWeapon)
	{
		//AttackMesh = ����
	}
	else
	{
		AttackMesh = MeshComp;
	}

	for (int32 i = 0; i < TargetSocketNames.Num(); ++i)
	{
		Locations[i] = AttackMesh->GetSocketLocation(TargetSocketNames[i]);
	}

	if (!MeshComp->GetOwner())
	{
		return;
	}
	// ��ȡ�Ŷӽӿ�
	OwnerTeamInterface = Cast<IGenericTeamAgentInterface>(MeshComp->GetOwner());
}

void UANS_AttackWindow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, TotalDuration, EventReference);

	// ���MeshComp��Ч��
	if (!MeshComp)
		return;

	// ���ӵ���ߺ�����ϵͳ�����Ч��
	if (!MeshComp->GetOwner() || !UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner()))
	{
		return;
	}

	FGameplayEventData Data;					// ���ڴ洢����Ŀ������
	AActor* OwnerActor = MeshComp->GetOwner();

	TArray<AActor*> IgnoredActors;				//���Ե�Actor
	if (bIgnoreOwner)
	{
		IgnoredActors.Add(OwnerActor);			// ��������
	}

	for (int32 i = 1; i < Locations.Num(); i++)
	{
		// ��һ֡λ��Ϊ��㣬��ǰ֡λ��Ϊ�յ�
		FVector StartLoc = Locations[i];
		FVector EndLoc = AttackMesh->GetSocketLocation(TargetSocketNames[i]);

		// ���ü���������ΪPawn
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // ֻ���Pawn����
		TArray<FHitResult> HitResults; // ���ڴ洢���н��

		EDrawDebugTrace::Type DrawDebugTrace = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;


		// ���ζ��ؼ�⣬����·���ϵ�����Ŀ��
		UKismetSystemLibrary::SphereTraceMultiForObjects(MeshComp, StartLoc, EndLoc, SphereSweepRadius,
			ObjectTypes, false, IgnoredActors, DrawDebugTrace, HitResults, false);

		// �����������н��
		for (const FHitResult& HitResult : HitResults)
		{
			AActor* HitActor = HitResult.GetActor();
			// �����Ѽ�¼��Actor
			if (!HitActor || HitActors.Contains(HitActor))
			{
				continue;
			}
			HitActors.AddUnique(HitActor);

			// ���Ŀ����Ӫ��ϵ����ֻ�������ˣ�
			// if (OwnerTeamInterface.IsValid())
			// {
			// 	if (OwnerTeamInterface->GetTeamAttitudeTowards(*HitResult.GetActor()) != TargetTeam)
			// 	{
			// 		continue;
			// 	}
			// }

			// ����Ŀ�����ݲ������¼�����
			FGameplayAbilityTargetData_SingleTargetHit* TargetHit = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
			Data.TargetData.Add(TargetHit);
		}
	}
	// ��ӵ���߷���GameplayEvent��������������Ŀ������
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, EventTag, Data);

	// ����λ��
	for (int32 i = 0; i < TargetSocketNames.Num(); ++i)
	{
		Locations[i] = AttackMesh->GetSocketLocation(TargetSocketNames[i]);
	}
}

void UANS_AttackWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	// �������
	Locations.Empty(0);
	HitActors.Empty(0);

	// ��ʽ���� Weak ָ�룬��֪���Ӳ��Ӻã���ָ��Ӧ�ò��ùܰɣ��ҽ�ai����Ū��һ�����
	AttackMesh.Reset();
	OwnerTeamInterface.Reset();
}

void UANS_AttackWindow::SendLocalGameplayCue(const FHitResult& HitResult) const
{
	FGameplayCueParameters CueParam;
	CueParam.Location = HitResult.Location;
	CueParam.Normal = HitResult.ImpactNormal;

	// ����������Ҫ������GameplayCue��ǩ
	for (const FGameplayTag& GameplayCueTag : TriggerGameplayCueTags)
	{
		UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(HitResult.GetActor(), GameplayCueTag, EGameplayCueEvent::Executed, CueParam);
	}
}
