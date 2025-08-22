// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AN_SendTargetGroup.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GenericTeamAgentInterface.h"

void UAN_SendTargetGroup::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp																											// 检查MeshComp有效性
		&& TargetSocketNames.Num() <= 1																						// 至少需要两个Socket才能进行连线检测
		&& (!MeshComp->GetOwner() || !UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner())))		// 检查拥有者和能力系统组件有效性
	{
		return;
	}

	FGameplayEventData Data;					// 用于存储命中目标数据
	TSet<AActor*> HitActors;					// 记录已命中的Actor，避免重复
	AActor* OwnerActor = MeshComp->GetOwner();

	for (int32 i = 1; i < TargetSocketNames.Num(); i++)
	{
		// 获取攻击的前一个位置和当前位置
		FVector StartLoc = MeshComp->GetSocketLocation(TargetSocketNames[i-1]);
		FVector EndLoc = MeshComp->GetSocketLocation(TargetSocketNames[i]);

		// 设置检测对象类型为Pawn
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn)); // 只检测Pawn类型
		TArray<FHitResult> HitResults; // 用于存储命中结果
		const IGenericTeamAgentInterface* OwnerTeamInterface = Cast<IGenericTeamAgentInterface>(OwnerActor);

		TArray<AActor*> IgnoredActors; // 忽略的Actor
		if (bIgnoreOwner)
		{
			IgnoredActors.Add(OwnerActor);// 忽略自身
		}
		EDrawDebugTrace::Type DrawDebugTrace = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

		// 球形多重检测，查找路径上的所有目标
		UKismetSystemLibrary::SphereTraceMultiForObjects(MeshComp, StartLoc, EndLoc, SphereSweepRadius, 
			ObjectTypes, false, IgnoredActors, DrawDebugTrace, HitResults, false);

		// 遍历所有命中结果
		for (const FHitResult& HitResult : HitResults)
		{
			// 忽略已记录的Actor
			if (HitActors.Contains(HitResult.GetActor()))
			{
				continue;
			}
			HitActors.Add(HitResult.GetActor());
			// 创建命中数据并添加到事件数据中
			FGameplayAbilityTargetData_SingleTargetHit* TargetHit = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
			Data.TargetData.Add(TargetHit);
		}
	}
	// 向拥有者发送GameplayEvent，带上所有命中目标数据
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, EventTag, Data);
}
