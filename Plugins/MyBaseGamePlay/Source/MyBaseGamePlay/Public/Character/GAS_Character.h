// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h" // IAbilitySystemInterface接口的头文件
#include "Components/WidgetComponent.h"
#include "Gameplay/OverHeadStatsGauge.h"
#include "GAS/GAS_AbilitySystemComponent.h"
#include "GAS/GAS_AttributeSet.h"
#include "GAS_Character.generated.h"

UCLASS()
class MYBASEGAMEPLAY_API AGAS_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGAS_Character();

	/****网络相关****/
	// 服务器中初始化
	void ServerSideInit();
	// 客户端中初始化
	void ClientSideInit();
	// 服务器中调用
	virtual void PossessedBy(AController* NewController) override;

	// 判断该角色是否由本地玩家控制
	bool IsLocallyControlledByPlayer() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//GAS组件相关
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

//UI相关组件
private:
	void ConfigureOverHeadStatusWidget();
	void ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComponent, UOverHeadStatsGauge* OverHeadStatsGauge);

	/**
	 * @brief 更新头顶状态条可见性\n
	 * 根据玩家与角色之间的距离判断是否启用头顶UI组件的显示。\n
	 * 该方法通过定时器周期性调用。
	 */
	void UpdateHeadGaugeVisibility();
	// 头顶UI
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> OverHeadWidgetComponent;
	/**
	 * @brief 头顶状态条更新间隔时间（秒）\n
	 * 控制头顶UI显示/隐藏检测的刷新频率，单位为秒。\n
	 * 可在编辑器中调整，默认值为1秒。
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityCheckUpdateGap = 1.f;
	/**
	 * @brief 头顶状态条可见性检测的距离平方阈值\n
	 * 当玩家与角色之间的距离平方小于该值时，显示头顶UI；\n
	 * 可在编辑器中调整，默认值为10,000,000。
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityRangeSquared = 10000000.f;
	// 用于控制头顶状态条可见性更新的定时器句柄
	FTimerHandle HeadStatGaugeVisibilityUpdateTimerHandle;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	TObjectPtr<UGAS_AbilitySystemComponent> GAS_AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UGAS_AttributeSet> GAS_AttributeSet;

};
