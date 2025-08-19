// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Core/GAS_AbilitySystemStatics.h"

FGameplayTag UGAS_AbilitySystemStatics::GetBasicAttackAbilityTag()
{
	// 如果不喜欢用代码创建tag可以用下列方法，感觉有打错字的风险
	// 可以使用这种方法来获取到tag
	//return FGameplayTag::RequestGameplayTag("ability.basic attack");

	// 在cpp函数中定义的tag的获取方法如下
	return TGameplayTags::Ability_BasicAttack;
}
