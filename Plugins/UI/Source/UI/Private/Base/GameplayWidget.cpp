// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GameplayWidget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OwnerAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
}

UValueGauge* UGameplayWidget::GetHealthBar()
{
	return HealthBar;
}

UValueGauge* UGameplayWidget::GetManaBar()
{
	return ManaBar;
}
