// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Core/GAS_GameplayAbility.h"
#include "GA_Combo.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API UGA_Combo : public UGAS_GameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	// Tag�����¼���
	UFUNCTION()
	void ComboChangedEventReceived(FGameplayEventData Data);

	/**
	 * @brief ���ü����������밴�µ��첽����
	 *
	 * �ú������ڴ�������ʼ��һ���ȴ���Ұ����������������
	 * ͨ����������������ʱ���á�
	 */
	void SetupWaitComboInputPress();

	/**
	 * @brief �����������밴�µĻص�����
	 *
	 * ����Ұ�����������ʱ�����˺���������ִ�������߼���
	 * ���л�����һ�������׶λ򲥷���һ�ζ�����
	 *
	 * @param TimeWaited ���밴��ǰ�ĵȴ�ʱ�䣨�룩
	 */
	UFUNCTION()
	void HandleInputPress(float TimeWaited);

	/**
	 * @brief �����ύ��ǰ��������
	 *
	 * �ú������ڼ���Ƿ������������������������Լ�����һ�������׶Ρ�
	 * �����������㣬�������������״̬����Դ˴����롣
	 */
	void TryCommitCombo();

	//��������˺�Tag�Ĵ���
	UFUNCTION()
	void DoDamage(FGameplayEventData Data);

	// ��ȡ��ǰ�������˺�Ч��
	TSubclassOf<UGameplayEffect> GetDamageEffectForCurrentCombo() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> ComboMontage;

	// �洢��һ��combo����
	FName NextComboName;

	// Ĭ���˺�Ч����
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effect")
	TSubclassOf<UGameplayEffect> DefaultDamageEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effect")
	TMap<FName, TSubclassOf<UGameplayEffect>> DamageEffectMap;
};
