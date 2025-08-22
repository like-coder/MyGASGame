// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AN_SendTargetGroup.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GenericTeamAgentInterface.h"

void UAN_SendTargetGroup::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp																											// ���MeshComp��Ч��
		&& TargetSocketNames.Num() <= 1																						// ������Ҫ����Socket���ܽ������߼��
		&& (!MeshComp->GetOwner() || !UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner())))		// ���ӵ���ߺ�����ϵͳ�����Ч��
	{
		return;
	}

	FGameplayEventData Data;					// ���ڴ洢����Ŀ������
	TSet<AActor*> HitActors;					// ��¼�����е�Actor�������ظ�
	AActor* OwnerActor = MeshComp->GetOwner();

	for (int32 i = 1; i < TargetSocketNames.Num(); i++)
	{
		// ��ȡ������ǰһ��λ�ú͵�ǰλ��
		FVector StartLoc = MeshComp->GetSocketLocation(TargetSocketNames[i-1]);
		FVector EndLoc = MeshComp->GetSocketLocation(TargetSocketNames[i]);

		// ���ü���������ΪPawn
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // ֻ���Pawn����
		TArray<FHitResult> HitResults; // ���ڴ洢���н��
		const IGenericTeamAgentInterface* OwnerTeamInterface = Cast<IGenericTeamAgentInterface>(OwnerActor);

		TArray<AActor*> IgnoredActors; // ���Ե�Actor
		if (bIgnoreOwner)
		{
			IgnoredActors.Add(OwnerActor);// ��������
		}
		EDrawDebugTrace::Type DrawDebugTrace = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

		// ���ζ��ؼ�⣬����·���ϵ�����Ŀ��
		UKismetSystemLibrary::SphereTraceMultiForObjects(MeshComp, StartLoc, EndLoc, SphereSweepRadius, 
			ObjectTypes, false, IgnoredActors, DrawDebugTrace, HitResults, false);

		// �����������н��
		for (const FHitResult& HitResult : HitResults)
		{
			// �����Ѽ�¼��Actor
			if (HitActors.Contains(HitResult.GetActor()))
			{
				continue;
			}
			HitActors.Add(HitResult.GetActor());
			// �����������ݲ���ӵ��¼�������
			FGameplayAbilityTargetData_SingleTargetHit* TargetHit = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
			Data.TargetData.Add(TargetHit);
		}
	}
	// ��ӵ���߷���GameplayEvent��������������Ŀ������
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, EventTag, Data);
}
