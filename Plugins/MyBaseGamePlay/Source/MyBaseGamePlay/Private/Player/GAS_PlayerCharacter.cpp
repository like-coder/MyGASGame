// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GAS_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AGAS_PlayerCharacter::AGAS_PlayerCharacter()
{
	// ������������������ɱ����
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent()); // �����ɱ�������ӵ���ɫ�ĸ����
	CameraBoom->bUsePawnControlRotation = true; // ʹ��Pawn������ת
	CameraBoom->TargetArmLength = 800.0f; // ���õ��ɱ۵ĳ���Ϊ800
	CameraBoom->SetRelativeLocation(FVector(0.0f, 50.0f, 0.0f));// ���õ��ɱ۵ĸ߶�Ϊ50

	// �����������ӽ���������
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // ���ӽ���������ӵ����ɱ������ָ�����

	// ���ý�ɫ��ת��Ϊ
	bUseControllerRotationYaw = false; // ���ÿ�������Yaw��ת
	GetCharacterMovement()->bOrientRotationToMovement = true; // ��ת��ɫ��ƥ���ƶ�����
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ���ý�ɫ����ת����
}

void AGAS_PlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (APlayerController* PlayerController = GetController<APlayerController>())
	{
		// ��ȡ����ҿ����������ı�����Ҷ���
		if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			// �Ƴ����е�����ӳ��������
			InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
			// �����������ӳ�������ģ����ȼ�Ϊ0��ȷ�������ȼ���
			InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
		}
	}
}

void AGAS_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// ������������
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AGAS_PlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AGAS_PlayerCharacter::HandleLookInput);
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AGAS_PlayerCharacter::HandleMoveInput);
		
		// �󶨼�������
		// �󶨼�������
		for (const TPair<ECAbilityInputID, TObjectPtr<UInputAction>>& InputActionPair : GameplayAbilityInputActions)
		{
			EnhancedInputComponent->BindAction(InputActionPair.Value, ETriggerEvent::Triggered, this, &AGAS_PlayerCharacter::HandleAbilityInput, InputActionPair.Key);
		}
	}
}

void AGAS_PlayerCharacter::HandleLookInput(const FInputActionValue& InputActionValue)
{
	// ������ֵ��FVector2Dת��ΪFVector2D����
	const FVector2D InputVal = InputActionValue.Get<FVector2D>();

	// ��������ֵ������ҵĸ�����(pitch)
	AddControllerPitchInput(-InputVal.Y);
	// ��������ֵ������ҵ�ƫ����(yaw)
	AddControllerYawInput(InputVal.X);
}

FVector AGAS_PlayerCharacter::GetLookRightDir() const
{
	//ViewCamera���Ҳ෽������
	return ViewCamera->GetRightVector();
}

FVector AGAS_PlayerCharacter::GetLookFwdDir() const
{
	//ViewCamera��ǰ��������
	return ViewCamera->GetForwardVector();
}

FVector AGAS_PlayerCharacter::GetMoveFwdDir() const
{
	//ͨ���Ҳ෽�����������Ϸ��������Ĳ���õ���ǰ���ƶ���������
	return FVector::CrossProduct(GetLookRightDir(), FVector::UpVector);
}

void AGAS_PlayerCharacter::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	// ��ȡ����ֵ��ת��ΪFVector2D����
	FVector2D InputVal = InputActionValue.Get<FVector2D>();
	// ������ֵ���й�һ������
	InputVal.Normalize();
	// ���ݴ���������ֵ������ҵ��ƶ�����
	AddMovementInput(GetMoveFwdDir() * InputVal.Y + GetLookRightDir() * InputVal.X);
}

void AGAS_PlayerCharacter::HandleAbilityInput(const FInputActionValue& InputActionValue, ECAbilityInputID InputID)
{
	bool bPressed = InputActionValue.Get<bool>();
	// ����
	if (bPressed)
	{
		GetAbilitySystemComponent()->AbilityLocalInputPressed(static_cast<int32>(InputID));
	}
	else
	{
		GetAbilitySystemComponent()->AbilityLocalInputReleased(static_cast<int32>(InputID));
	}
}
