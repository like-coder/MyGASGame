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
	// 预构造函数
	virtual void NativePreConstruct() override;
	/**
	 * @brief 绑定到游戏属性并设置当前值与最大值
	 *
	 * 将该数值指示器绑定到指定的能力系统组件中的游戏属性，
	 * 同时也绑定到对应的最大值属性。当属性值发生变化时，
	 * 指示器会自动更新显示。
	 *
	 * @param AbilitySystemComponent 能力系统组件，用于注册和监听属性变化
	 * @param Attribute 当前值的游戏属性
	 * @param MaxAttribute 最大值的游戏属性
	 */
	void SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute);
	void SetValue(float NewValue, float NewMaxValue);
	//设置进度条颜色
	void SetBarColor(FLinearColor NewBarColor);

private:
	// 回调用函数
	void ValueChanged(const FOnAttributeChangeData& ChangeData);
	void MaxValueChanged(const FOnAttributeChangeData& ChangeData);

	// 缓存属性
	float CachedValue;
	float CachedMaxValue;

private:
	// 设置进度条的颜色
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor BarColor;

	UPROPERTY(EditAnywhere, Category = "Visual")
	float TextSize = 10;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ValueText;
};
