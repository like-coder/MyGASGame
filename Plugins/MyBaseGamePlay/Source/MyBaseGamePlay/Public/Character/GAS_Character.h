// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h" // IAbilitySystemInterface�ӿڵ�ͷ�ļ�
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

	/****�������****/
	// �������г�ʼ��
	void ServerSideInit();
	// �ͻ����г�ʼ��
	void ClientSideInit();
	// �������е���
	virtual void PossessedBy(AController* NewController) override;

	// �жϸý�ɫ�Ƿ��ɱ�����ҿ���
	bool IsLocallyControlledByPlayer() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//GAS������
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

//UI������
private:
	void ConfigureOverHeadStatusWidget();
	void ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComponent, UOverHeadStatsGauge* OverHeadStatsGauge);

	/**
	 * @brief ����ͷ��״̬���ɼ���\n
	 * ����������ɫ֮��ľ����ж��Ƿ�����ͷ��UI�������ʾ��\n
	 * �÷���ͨ����ʱ�������Ե��á�
	 */
	void UpdateHeadGaugeVisibility();
	// ͷ��UI
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> OverHeadWidgetComponent;
	/**
	 * @brief ͷ��״̬�����¼��ʱ�䣨�룩\n
	 * ����ͷ��UI��ʾ/���ؼ���ˢ��Ƶ�ʣ���λΪ�롣\n
	 * ���ڱ༭���е�����Ĭ��ֵΪ1�롣
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityCheckUpdateGap = 1.f;
	/**
	 * @brief ͷ��״̬���ɼ��Լ��ľ���ƽ����ֵ\n
	 * ��������ɫ֮��ľ���ƽ��С�ڸ�ֵʱ����ʾͷ��UI��\n
	 * ���ڱ༭���е�����Ĭ��ֵΪ10,000,000��
	 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityRangeSquared = 10000000.f;
	// ���ڿ���ͷ��״̬���ɼ��Ը��µĶ�ʱ�����
	FTimerHandle HeadStatGaugeVisibilityUpdateTimerHandle;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	TObjectPtr<UGAS_AbilitySystemComponent> GAS_AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UGAS_AttributeSet> GAS_AttributeSet;

};
