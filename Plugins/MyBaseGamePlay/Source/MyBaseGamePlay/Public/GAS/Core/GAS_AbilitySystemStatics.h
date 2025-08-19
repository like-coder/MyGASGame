// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TGameplayTags.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GAS_AbilitySystemStatics.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API UGAS_AbilitySystemStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static FGameplayTag GetBasicAttackAbilityTag();
};
