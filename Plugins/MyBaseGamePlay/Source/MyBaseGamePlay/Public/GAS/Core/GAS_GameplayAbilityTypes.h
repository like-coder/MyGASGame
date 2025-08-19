// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GAS_GameplayAbilityTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECAbilityInputID : uint8
{
	None							UMETA(DisplayName = "None"),
	BasicAttack						UMETA(DisplayName = "基础攻击"),
	Aim								UMETA(DisplayName = "Aim"),
	AbilityOne						UMETA(DisplayName = "一技能"),
	AbilityTwo						UMETA(DisplayName = "二技能"),
	AbilityThree					UMETA(DisplayName = "三技能"),
	AbilityFour						UMETA(DisplayName = "四技能"),
	AbilityFive						UMETA(DisplayName = "五技能"),
	AbilitySix						UMETA(DisplayName = "六技能"),
	Confirm							UMETA(DisplayName = "确认"),
	Cancel							UMETA(DisplayName = "取消")
};