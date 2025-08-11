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
	 * 动画实例原生初始化覆盖点
	 * 用于执行动画实例的初始化逻辑，在实例创建时调用
	 */
	virtual void NativeInitializeAnimation() override;

	/**
	 * 动画实例原生更新覆盖点
	 * 主要用于在游戏线程中收集动画数据，实际计算建议放在 NativeThreadSafeUpdateAnimation 中
	 *
	 * @param DeltaSeconds 当前帧与上一帧之间的时间间隔（秒）
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
	 * 当前帧的移动速度
	 * 用于判断角色移动状态
	 */
	float Speed;

	/**
	 * 当前帧的偏航角速度
	 * 用于计算角色在水平面上的旋转速度
	 */
	float YawSpeed;
	/**
	 * 平滑后的偏航角速度
	 *  用于在多个帧之间平滑偏航角速度，以减少抖动
	 */
	float SmoothedYawSpeed;
	/**
	 * 平滑插值的速度
	 * 控制偏航角速度从当前值平滑过渡到零的速度
	 */
	UPROPERTY(EditAnywhere, Category = "Animation")
	float YawSpeedSmoothLerpSpeed = 1.f;

	/**
	 * 当偏航角速度降到零时使用的插值速度
	 * 用于控制偏航角速度从当前值平滑过渡到零的加速度
	 */
	UPROPERTY(EditAnywhere, Category = "Animation")
	float YawSpeedLerpToZeroSpeed = 30.f;

	/**
	 * 是否正在跳跃
	 */
	bool bIsJumping;

	/**
	 * 前一帧的角色旋转
	 * 用于计算当前帧的旋转变化量
	 */
	FRotator BodyPrevRotator;

};
