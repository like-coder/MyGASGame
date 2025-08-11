// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GAS_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API UGAS_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UGAS_AnimInstance();
	/**
	 * ����ʵ��ԭ����ʼ�����ǵ�
	 * ����ִ�ж���ʵ���ĳ�ʼ���߼�����ʵ������ʱ����
	 */
	virtual void NativeInitializeAnimation() override;

	/**
	 * ����ʵ��ԭ�����¸��ǵ�
	 * ��Ҫ��������Ϸ�߳����ռ��������ݣ�ʵ�ʼ��㽨����� NativeThreadSafeUpdateAnimation ��
	 *
	 * @param DeltaSeconds ��ǰ֡����һ֮֡���ʱ�������룩
	 */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	float GetSpeed() const { return Speed; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool IsMoving() const { return Speed != 0; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool IsNotMoving() const { return Speed == 0; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	float GetYawSpeed() const { return YawSpeed; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	float GetSmoothedYawSpeed() const { return SmoothedYawSpeed; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool GetIsJumping() const { return bIsJumping; }

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool GetIsOnGround() const { return !bIsJumping; }

private:
	UPROPERTY()
	TObjectPtr<class ACharacter> OwnerCharacter;

	UPROPERTY()
	TObjectPtr<class UCharacterMovementComponent> OwnerMovementComponent;

	/**
	 * ��ǰ֡���ƶ��ٶ�
	 * �����жϽ�ɫ�ƶ�״̬
	 */
	float Speed;

	/**
	 * ��ǰ֡��ƫ�����ٶ�
	 * ���ڼ����ɫ��ˮƽ���ϵ���ת�ٶ�
	 */
	float YawSpeed;
	/**
	 * ƽ�����ƫ�����ٶ�
	 *  �����ڶ��֮֡��ƽ��ƫ�����ٶȣ��Լ��ٶ���
	 */
	float SmoothedYawSpeed;
	/**
	 * ƽ����ֵ���ٶ�
	 * ����ƫ�����ٶȴӵ�ǰֵƽ�����ɵ�����ٶ�
	 */
	UPROPERTY(EditAnywhere, Category = "Animation")
	float YawSpeedSmoothLerpSpeed = 1.f;

	/**
	 * ��ƫ�����ٶȽ�����ʱʹ�õĲ�ֵ�ٶ�
	 * ���ڿ���ƫ�����ٶȴӵ�ǰֵƽ�����ɵ���ļ��ٶ�
	 */
	UPROPERTY(EditAnywhere, Category = "Animation")
	float YawSpeedLerpToZeroSpeed = 30.f;

	/**
	 * �Ƿ�������Ծ
	 */
	bool bIsJumping;

	/**
	 * ǰһ֡�Ľ�ɫ��ת
	 * ���ڼ��㵱ǰ֡����ת�仯��
	 */
	FRotator BodyPrevRotator;

};
