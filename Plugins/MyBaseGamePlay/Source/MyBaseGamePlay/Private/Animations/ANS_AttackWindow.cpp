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

	// 初始化
	Locations.SetNum(TargetSocketNames.Num());
	// 如果用武器
	if (bUseWeapon)
	{
		//AttackMesh = 武器
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
	// 获取团队接口
	OwnerTeamInterface = Cast<IGenericTeamAgentInterface>(MeshComp->GetOwner());
}

void UANS_AttackWindow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, TotalDuration, EventReference);

	// 检查MeshComp有效性
	if (!MeshComp)
		return;

	// 检查拥有者和能力系统组件有效性
	if (!MeshComp->GetOwner() || !UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner()))
	{
		return;
	}

	FGameplayEventData Data;					// 用于存储命中目标数据
	AActor* OwnerActor = MeshComp->GetOwner();

	TArray<AActor*> IgnoredActors;				//忽略的Actor
	if (bIgnoreOwner)
	{
		IgnoredActors.Add(OwnerActor);			// 忽略自身
	}

	for (int32 i = 1; i < Locations.Num(); i++)
	{
		// 上一帧位置为起点，当前帧位置为终点
		FVector StartLoc = Locations[i];
		FVector EndLoc = AttackMesh->GetSocketLocation(TargetSocketNames[i]);

		// 设置检测对象类型为Pawn
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // 只检测Pawn类型
		TArray<FHitResult> HitResults; // 用于存储命中结果

		EDrawDebugTrace::Type DrawDebugTrace = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;


		// 球形多重检测，查找路径上的所有目标
		UKismetSystemLibrary::SphereTraceMultiForObjects(MeshComp, StartLoc, EndLoc, SphereSweepRadius,
			ObjectTypes, false, IgnoredActors, DrawDebugTrace, HitResults, false);

		// 遍历所有命中结果
		for (const FHitResult& HitResult : HitResults)
		{
			AActor* HitActor = HitResult.GetActor();
			// 忽略已记录的Actor
			if (!HitActor || HitActors.Contains(HitActor))
			{
				continue;
			}
			HitActors.AddUnique(HitActor);

			// 检查目标阵营关系（如只攻击敌人）
			// if (OwnerTeamInterface.IsValid())
			// {
			// 	if (OwnerTeamInterface->GetTeamAttitudeTowards(*HitResult.GetActor()) != TargetTeam)
			// 	{
			// 		continue;
			// 	}
			// }

			// 构造目标数据并加入事件数据
			FGameplayAbilityTargetData_SingleTargetHit* TargetHit = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
			Data.TargetData.Add(TargetHit);
		}
	}
	// 向拥有者发送GameplayEvent，带上所有命中目标数据
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, EventTag, Data);

	// 更新位置
	for (int32 i = 0; i < TargetSocketNames.Num(); ++i)
	{
		Locations[i] = AttackMesh->GetSocketLocation(TargetSocketNames[i]);
	}
}

void UANS_AttackWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	// 清空数据
	Locations.Empty(0);
	HitActors.Empty(0);

	// 显式重置 Weak 指针，不知道加不加好，弱指针应该不用管吧，我叫ai给我弄了一坨出来
	AttackMesh.Reset();
	OwnerTeamInterface.Reset();
}

void UANS_AttackWindow::SendLocalGameplayCue(const FHitResult& HitResult) const
{
	FGameplayCueParameters CueParam;
	CueParam.Location = HitResult.Location;
	CueParam.Normal = HitResult.ImpactNormal;

	// 遍历所有需要触发的GameplayCue标签
	for (const FGameplayTag& GameplayCueTag : TriggerGameplayCueTags)
	{
		UAbilitySystemGlobals::Get().GetGameplayCueManager()->HandleGameplayCue(HitResult.GetActor(), GameplayCueTag, EGameplayCueEvent::Executed, CueParam);
	}
}
