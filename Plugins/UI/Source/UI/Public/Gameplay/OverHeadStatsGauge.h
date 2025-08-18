// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/ValueGauge.h"
#include "Blueprint/UserWidget.h"
#include "OverHeadStatsGauge.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UOverHeadStatsGauge : public UUserWidget
{
	GENERATED_BODY()
public:
	UValueGauge* GetHealthBar();
	UValueGauge* GetManaBar();
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> HealthBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> ManaBar;
};
