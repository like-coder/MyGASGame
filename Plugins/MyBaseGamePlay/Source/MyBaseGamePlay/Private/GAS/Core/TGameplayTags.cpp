// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Core/TGameplayTags.h"


namespace TGameplayTags
{
	// ""双引号内的是tag的定义名称，第二条的是是可以添加注释的方法
	//UE_DEFINE_GAMEPLAY_TAG(Ability_BasicAttack, "Ability.BasicAttack")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_BasicAttack, "Ability.BasicAttack", "基础攻击能力");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combo_Change, "Ability.Combo.Change", "连击切换");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combo_Change_Combo02, "Ability.Combo.Change.Combo02", "连击切换连段2");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combo_Change_Combo03, "Ability.Combo.Change.Combo03", "连击切换连段3");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combo_Change_Combo04, "Ability.Combo.Change.Combo04", "连击切换连段4");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combo_Change_End, "Ability.Combo.Change.End", "连击切换结束");

}