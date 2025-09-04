// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/ValueGauge.h"
#include "Blueprint/UserWidget.h"
#include "GenericTeamAgentInterface.h"
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

	//设置血条颜色
	void SetHealthBarColor(ETeamAttitude::Type TargetTeam);
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> HealthBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> ManaBar;

	// 我方血条颜色
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor FriendlyColor;
	// 敌方血条颜色
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor HostileColor;
};
