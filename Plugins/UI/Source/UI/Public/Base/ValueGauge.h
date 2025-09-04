// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameplayEffectTypes.h"
#include "ValueGauge.generated.h"

/**
 * 
 */
UCLASS()
class UI_API UValueGauge : public UUserWidget
{
	GENERATED_BODY()
public:
	// Ԥ���캯��
	virtual void NativePreConstruct() override;
	/**
	 * @brief �󶨵���Ϸ���Բ����õ�ǰֵ�����ֵ
	 *
	 * ������ֵָʾ���󶨵�ָ��������ϵͳ����е���Ϸ���ԣ�
	 * ͬʱҲ�󶨵���Ӧ�����ֵ���ԡ�������ֵ�����仯ʱ��
	 * ָʾ�����Զ�������ʾ��
	 *
	 * @param AbilitySystemComponent ����ϵͳ���������ע��ͼ������Ա仯
	 * @param Attribute ��ǰֵ����Ϸ����
	 * @param MaxAttribute ���ֵ����Ϸ����
	 */
	void SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute);
	void SetValue(float NewValue, float NewMaxValue);
	//���ý�������ɫ
	void SetBarColor(FLinearColor NewBarColor);

private:
	// �ص��ú���
	void ValueChanged(const FOnAttributeChangeData& ChangeData);
	void MaxValueChanged(const FOnAttributeChangeData& ChangeData);

	// ��������
	float CachedValue;
	float CachedMaxValue;

private:
	// ���ý���������ɫ
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor BarColor;

	UPROPERTY(EditAnywhere, Category = "Visual")
	float TextSize = 10;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ValueText;
};
