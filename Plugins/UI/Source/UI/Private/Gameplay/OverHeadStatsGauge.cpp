// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/OverHeadStatsGauge.h"

UValueGauge* UOverHeadStatsGauge::GetHealthBar()
{
	return HealthBar;
}

UValueGauge* UOverHeadStatsGauge::GetManaBar()
{
	return ManaBar;
}
