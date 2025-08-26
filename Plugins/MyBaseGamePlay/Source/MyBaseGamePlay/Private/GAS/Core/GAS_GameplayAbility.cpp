// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Core/GAS_GameplayAbility.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"

UAnimInstance* UGAS_GameplayAbility::GetOwnerAnimInstance() const
{
    USkeletalMeshComponent* SkeletalMeshComp = GetOwningComponentFromActorInfo();
    if (SkeletalMeshComp)
    {
        return SkeletalMeshComp->GetAnimInstance();
    }
    return nullptr;
}

TArray<FHitResult> UGAS_GameplayAbility::GetHitResultFromSweepLocationTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle, float SphereSweepRadius, ETeamAttitude::Type TargetTeam, bool bDrawDebug, bool bIgnoreSelf) const
{
	TArray<FHitResult> OutResults; // �洢���շ��ص����н��
	TSet<AActor*> HitActors;      // ��¼�����е�Actor�������ظ�

	// ��ȡӵ����(Avatar)�Ķ���ӿ�
	IGenericTeamAgentInterface* OwnerTeamInterface = Cast<IGenericTeamAgentInterface>(GetAvatarActorFromActorInfo());

	// ��������Ŀ������
	for (const TSharedPtr<FGameplayAbilityTargetData>& TargetData : TargetDataHandle.Data)
	{
		// ��ȡɨ�������յ�
		FVector StartLoc = TargetData->GetOrigin().GetTranslation();
		FVector EndLoc = TargetData->GetEndPoint();

		// ����Ҫ���Ķ�������(����ֻ���Pawn)
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		// ����Ҫ���Ե�Actor(�����Ҫ�����Լ�)
		TArray<AActor*> ActorsToIgnore;
		if (bIgnoreSelf)
		{
			ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
		}

		// ���õ��Ի���ģʽ
		EDrawDebugTrace::Type DrawDebugTrace = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

		// ִ�����ζ����ɨ��
		TArray<FHitResult> Results;
		UKismetSystemLibrary::SphereTraceMultiForObjects(this, StartLoc, EndLoc, SphereSweepRadius, ObjectTypes, false, ActorsToIgnore, DrawDebugTrace, Results, false);

		// ����ɨ����
		for (const FHitResult& Result : Results)
		{
			// ����Ѿ����й���Actor��������
			if (HitActors.Contains(Result.GetActor()))
			{
				continue;
			}

			// �������ϵ(��������˶������)
			if (OwnerTeamInterface)
			{
				ETeamAttitude::Type OtherActorTeamAttitude = OwnerTeamInterface->GetTeamAttitudeTowards(*Result.GetActor());
				if (OtherActorTeamAttitude != TargetTeam)
				{
					continue;
				}
			}

			// ��¼���е�Actor����ӽ��
			HitActors.Add(Result.GetActor());
			OutResults.Add(Result);
		}
	}

	return OutResults; // ����������Ч���н��
}

void UGAS_GameplayAbility::ApplyGameplayEffectToHitResultActor(const FHitResult& HitResult, TSubclassOf<UGameplayEffect> GameplayEffect, int Level)
{
	// ����һ��������ϷЧ���淶���������ָ����GameplayEffect�͵ȼ�
	FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(GameplayEffect, Level);

	// ����һ����ϷЧ�������ľ����������ǰ�����淶����͵�ǰActor��Ϣ
	FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo());

	// ����������������н����Ϣ
	EffectContextHandle.AddHitResult(HitResult);

	// �����������õ�Ч���淶������
	EffectSpecHandle.Data->SetContext(EffectContextHandle);

	ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(),
		GetCurrentActivationInfo(), EffectSpecHandle, UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitResult.GetActor()));
}
