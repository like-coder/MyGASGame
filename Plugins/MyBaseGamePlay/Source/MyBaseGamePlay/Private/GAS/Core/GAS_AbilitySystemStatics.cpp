// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Core/GAS_AbilitySystemStatics.h"

FGameplayTag UGAS_AbilitySystemStatics::GetBasicAttackAbilityTag()
{
	// �����ϲ���ô��봴��tag���������з������о��д���ֵķ���
	// ����ʹ�����ַ�������ȡ��tag
	//return FGameplayTag::RequestGameplayTag("ability.basic attack");

	// ��cpp�����ж����tag�Ļ�ȡ��������
	return TGameplayTags::Ability_BasicAttack;
}
