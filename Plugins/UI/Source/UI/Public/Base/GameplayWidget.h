// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValueGauge.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// 当Widget被创建并添加到视口时，此函数会被自动调用
	virtual void NativeConstruct() override;

	UValueGauge* GetHealthBar();
	UValueGauge* GetManaBar();
	
private:
	// 生命进度条
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> HealthBar;

	// 法力进度条
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> ManaBar;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> OwnerAbilitySystemComponent;
};
