// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h" // IAbilitySystemInterface�ӿڵ�ͷ�ļ�
#include "GenericTeamAgentInterface.h"
#include "Components/WidgetComponent.h"
#include "Gameplay/OverHeadStatsGauge.h"
#include "GAS/GAS_AbilitySystemComponent.h"
#include "GAS/GAS_AttributeSet.h"
#include "GAS_Character.generated.h"

UCLASS()
class MYBASEGAMEPLAY_API AGAS_Character : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
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

//�Ŷ�(Team)
public:
	// �жϵ�ǰ�������һ�������̬��
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// �����Ŷ�ID
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	// ��ȡ�Ŷ�ID
	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	UFUNCTION()
	virtual void OnRep_TeamID();

	UPROPERTY(ReplicatedUsing = OnRep_TeamID)
	FGenericTeamId TeamID;

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

private:
	// ��GAS���Ըı�ί��
	void BindGASChangeDelegates();
	// ������ǩ����(NewCountΪ��ǩ����)
	void DeathTagUpdated(const FGameplayTag Tag, int32 NewCount);

//�����͸��� (Death and Respawn)
private:
	// ������̫����ɴ���
	void DeathMontageFinished();
	// ����/���� ������ϵͳ
	void SetRagdollEnabled(bool bIsEnabled);
	// ������������
	void PlayDeathAnimation();
	// ����
	void StartDeathSequence();
	// ����
	void Respawn();
	// ������ʵ��
	virtual void OnDead() {}
	virtual void OnRespawn() {}

	// ���������ı任
	FTransform MeshRelativeTransform;
	// ������̫�����ʱ��ƫ��
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	float DeathMontageFinishTimeShift = -0.8f;
	// ������̫��
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	TObjectPtr<UAnimMontage> DeathMontage;

	//������̫���ʱ�����
	FTimerHandle DeathMontageTimerHandle;

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
	/**
	 * @brief ����ͷ��״̬��������״̬\n
	 * ���û����ͷ��UI�������ʾ��\n
	 * @param bIsEnabled �Ƿ�����ͷ��UI
	 */
	void SetStatusGaugeEnabled(bool bIsEnabled);
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
