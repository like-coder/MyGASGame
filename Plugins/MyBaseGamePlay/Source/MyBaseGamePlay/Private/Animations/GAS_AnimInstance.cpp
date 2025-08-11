// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/GAS_AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UGAS_AnimInstance::UGAS_AnimInstance() : Speed(0)
{

}

void UGAS_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	// ��ȡOwnerת��Ϊ��ɫ
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		// ��ȡOwner���ƶ����
		OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UGAS_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (OwnerCharacter)
	{
		FVector Velocity = OwnerCharacter->GetVelocity();
		Speed = Velocity.Length();

		//��ȡ��ǰ������ת�Ƕ�����һ֡�Ĳ�ֵ�����ڼ�����ת�仯��
		FRotator BodyRotator = OwnerCharacter->GetActorRotation();
		FRotator BodyRotatorDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRotator, BodyPrevRotator);
		BodyPrevRotator = BodyRotator;

		//����yaw����ת�ٶȣ�ÿ����ת�Ƕȣ�
		YawSpeed = BodyRotatorDelta.Yaw / DeltaSeconds;

		// ���ƫ�����ٶ�Ϊ0����ʹ���ض����ٶȽ���ƽ����ֵ
		float YawLerpSpeed = YawSpeedSmoothLerpSpeed;
		if (YawSpeed == 0)
		{
			YawLerpSpeed = YawSpeedLerpToZeroSpeed;
		}
		// ʹ�����Բ�ֵ��FInterpTo���� yaw �ٶȽ���ƽ��������߶�����������
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawLerpSpeed);
	}
	
	if (OwnerMovementComponent)
	{
		bIsJumping = OwnerMovementComponent->IsFalling();
	}
}
