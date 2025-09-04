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

void UOverHeadStatsGauge::SetHealthBarColor(ETeamAttitude::Type TargetTeam)
{
	if (HealthBar)
	{
		switch (TargetTeam)
		{
		case ETeamAttitude::Friendly:
			HealthBar->SetBarColor(FriendlyColor);
			break;
		case ETeamAttitude::Hostile:
			HealthBar->SetBarColor(HostileColor);
			break;
		default:
			HealthBar->SetBarColor(FLinearColor::Yellow);
			break;
		}
	}
}
