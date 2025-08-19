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
	// 头顶UI
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> OverHeadWidgetComponent;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	TObjectPtr<UGAS_AbilitySystemComponent> GAS_AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UGAS_AttributeSet> GAS_AttributeSet;

};
