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
	 * �ڿͻ������¿�ʼʱ����
	 * ���ڴ�����ҽ�ɫ���������ʼ���߼�
	 */
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	/*************************Input**************************/
	// ���İ󶨺���
	void HandleLookInput(const FInputActionValue& InputActionValue);
	// �ƶ��İ󶨺���
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	// ��ȡ��ɫ�����Ҳ�ķ�������
	FVector GetLookRightDir() const;
	// ��ȡ��ɫ������ǰ�ķ�������
	FVector GetLookFwdDir() const;
	// �����ɫ��ǰ�ƶ��ķ�������
	FVector GetMoveFwdDir() const;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> JumpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> MoveInputAction;

	// ������Ϸ����ӳ��������
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> GameplayInputMappingContext;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	TObjectPtr<class UCameraComponent> ViewCamera;
};
