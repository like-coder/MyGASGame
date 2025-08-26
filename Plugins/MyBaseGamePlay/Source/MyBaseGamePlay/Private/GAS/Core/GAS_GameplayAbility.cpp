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
	TArray<FHitResult> OutResults; // 存储最终返回的命中结果
	TSet<AActor*> HitActors;      // 记录已命中的Actor，避免重复

	// 获取拥有者(Avatar)的队伍接口
	IGenericTeamAgentInterface* OwnerTeamInterface = Cast<IGenericTeamAgentInterface>(GetAvatarActorFromActorInfo());

	// 遍历所有目标数据
	for (const TSharedPtr<FGameplayAbilityTargetData>& TargetData : TargetDataHandle.Data)
	{
		// 获取扫描起点和终点
		FVector StartLoc = TargetData->GetOrigin().GetTranslation();
		FVector EndLoc = TargetData->GetEndPoint();

		// 设置要检测的对象类型(这里只检测Pawn)
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		// 设置要忽略的Actor(如果需要忽略自己)
		TArray<AActor*> ActorsToIgnore;
		if (bIgnoreSelf)
		{
			ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
		}

		// 设置调试绘制模式
		EDrawDebugTrace::Type DrawDebugTrace = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

		// 执行球形多对象扫描
		TArray<FHitResult> Results;
		UKismetSystemLibrary::SphereTraceMultiForObjects(this, StartLoc, EndLoc, SphereSweepRadius, ObjectTypes, false, ActorsToIgnore, DrawDebugTrace, Results, false);

		// 处理扫描结果
		for (const FHitResult& Result : Results)
		{
			// 如果已经命中过该Actor，则跳过
			if (HitActors.Contains(Result.GetActor()))
			{
				continue;
			}

			// 检查队伍关系(如果设置了队伍过滤)
			if (OwnerTeamInterface)
			{
				ETeamAttitude::Type OtherActorTeamAttitude = OwnerTeamInterface->GetTeamAttitudeTowards(*Result.GetActor());
				if (OtherActorTeamAttitude != TargetTeam)
				{
					continue;
				}
			}

			// 记录命中的Actor并添加结果
			HitActors.Add(Result.GetActor());
			OutResults.Add(Result);
		}
	}

	return OutResults; // 返回所有有效命中结果
}

void UGAS_GameplayAbility::ApplyGameplayEffectToHitResultActor(const FHitResult& HitResult, TSubclassOf<UGameplayEffect> GameplayEffect, int Level)
{
	// 创建一个传出游戏效果规范句柄，包含指定的GameplayEffect和等级
	FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(GameplayEffect, Level);

	// 创建一个游戏效果上下文句柄，包含当前能力规范句柄和当前Actor信息
	FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo());

	// 向上下文中添加命中结果信息
	EffectContextHandle.AddHitResult(HitResult);

	// 将上下文设置到效果规范数据中
	EffectSpecHandle.Data->SetContext(EffectContextHandle);

	ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(),
		GetCurrentActivationInfo(), EffectSpecHandle, UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitResult.GetActor()));
}
