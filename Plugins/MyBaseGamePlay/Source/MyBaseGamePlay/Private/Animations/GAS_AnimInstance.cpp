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
	// 获取Owner转换为角色
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerCharacter)
	{
		// 获取Owner的移动组件
		OwnerMovementComponent = OwnerCharacter->GetCharacterMovement();
	}
}

void UGAS_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (OwnerCharacter)
	{
		FVector Velocity = OwnerCharacter->GetVelocity();
		Speed = Velocity.Length();

		//获取当前身体旋转角度与上一帧的差值，用于计算旋转变化率
		FRotator BodyRotator = OwnerCharacter->GetActorRotation();
		FRotator BodyRotatorDelta = UKismetMathLibrary::NormalizedDeltaRotator(BodyRotator, BodyPrevRotator);
		BodyPrevRotator = BodyRotator;

		//计算yaw轴旋转速度（每秒旋转角度）
		YawSpeed = BodyRotatorDelta.Yaw / DeltaSeconds;

		// 如果偏航角速度为0，则使用特定的速度进行平滑插值
		float YawLerpSpeed = YawSpeedSmoothLerpSpeed;
		if (YawSpeed == 0)
		{
			YawLerpSpeed = YawSpeedLerpToZeroSpeed;
		}
		// 使用线性插值（FInterpTo）对 yaw 速度进行平滑处理，提高动画过渡质量
		SmoothedYawSpeed = UKismetMathLibrary::FInterpTo(SmoothedYawSpeed, YawSpeed, DeltaSeconds, YawLerpSpeed);
	}
	
	if (OwnerMovementComponent)
	{
		bIsJumping = OwnerMovementComponent->IsFalling();
	}
}
