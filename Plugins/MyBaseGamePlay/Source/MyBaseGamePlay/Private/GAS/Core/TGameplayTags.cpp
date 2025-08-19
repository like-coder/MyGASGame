// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Core/TGameplayTags.h"


namespace TGameplayTags
{
	// ""双引号内的是tag的定义名称，第二条的是是可以添加注释的方法
	//UE_DEFINE_GAMEPLAY_TAG(Ability_BasicAttack, "Ability.BasicAttack")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_BasicAttack, "Ability.BasicAttack", "基础攻击能力");

}