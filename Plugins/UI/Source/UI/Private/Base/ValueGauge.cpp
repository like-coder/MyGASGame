// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/ValueGauge.h"
#include "AbilitySystemComponent.h"

void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (ProgressBar->IsValidLowLevel())
	{
		ProgressBar->SetFillColorAndOpacity(BarColor);
	}
}

void UValueGauge::SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute)
{
	if (AbilitySystemComponent)
	{
		// ������ϵͳ����л�ȡ��ǰ����ֵ�����ֵ����ֵ
		bool bFound;
		float Value = AbilitySystemComponent->GetGameplayAttributeValue(Attribute, bFound);
		float MaxValue = AbilitySystemComponent->GetGameplayAttributeValue(MaxAttribute, bFound);

		// ����ɹ��ҵ���Ӧ������ֵ���������ֵָʾ������ʾ
		if (bFound)
		{
			SetValue(Value, MaxValue);
		}
		// ע�����Ա仯�ص���������ֵ�����仯ʱ������ֵָʾ����ʾ
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UValueGauge::ValueChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UValueGauge::MaxValueChanged);
	}
}

void UValueGauge::SetValue(const float NewValue, const float NewMaxValue)
{
	// ��������ֵ
	CachedValue = NewValue;
	CachedMaxValue = NewMaxValue;
	if (NewMaxValue == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Value Gauge: %s, �µ����ֵ����Ϊ0"), *GetName());
		return;
	}
	// ���ý������ٷֱ�
	ProgressBar->SetPercent(NewValue / NewMaxValue);
	// �������ָ�ʽѡ����С��λ��Ϊ0
	const FNumberFormattingOptions FormatOps = FNumberFormattingOptions().SetMaximumFractionalDigits(0);
	// �����ı���ʾ
	ValueText->SetText(
		FText::Format(
			FTextFormat::FromString("{0}/{1}"),			 // ��ʽ�ַ���
			FText::AsNumber(NewValue, &FormatOps),       // ��ǰֵ
			FText::AsNumber(NewMaxValue, &FormatOps)     // ���ֵ
		)
	);
}

void UValueGauge::ValueChanged(const FOnAttributeChangeData& ChangeData)
{
	SetValue(ChangeData.NewValue, CachedMaxValue);
}

void UValueGauge::MaxValueChanged(const FOnAttributeChangeData& ChangeData)
{
	SetValue(CachedValue, ChangeData.NewValue);
}
