// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/GAS_AnimInstance.h"
#include "GameFramework/Character.h"

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
	}

	if (OwnerMovementComponent)
	{

	}
}
