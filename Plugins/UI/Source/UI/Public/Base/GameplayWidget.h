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
	// ��Widget����������ӵ��ӿ�ʱ���˺����ᱻ�Զ�����
	virtual void NativeConstruct() override;

	UValueGauge* GetHealthBar();
	UValueGauge* GetManaBar();
	
private:
	// ����������
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> HealthBar;

	// ����������
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UValueGauge> ManaBar;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> OwnerAbilitySystemComponent;
};
