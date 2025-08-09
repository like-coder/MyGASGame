// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Character/GAS_Character.h"
#include "GAS_PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MYBASEGAMEPLAY_API AGAS_PlayerCharacter : public AGAS_Character
{
	GENERATED_BODY()
public:
	AGAS_PlayerCharacter();

	/**
	 * 在客户端重新开始时调用
	 * 用于处理玩家角色的重生或初始化逻辑
	 */
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	/*************************Input**************************/
	// 看的绑定函数
	void HandleLookInput(const FInputActionValue& InputActionValue);
	// 移动的绑定函数
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	// 获取角色视线右侧的方向向量
	FVector GetLookRightDir() const;
	// 获取角色视线向前的方向向量
	FVector GetLookFwdDir() const;
	// 计算角色向前移动的方向向量
	FVector GetMoveFwdDir() const;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> MoveInputAction;

	// 管理游戏输入映射上下文
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> GameplayInputMappingContext;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<class UCameraComponent> ViewCamera;
};
