// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h" // IAbilitySystemInterface�ӿڵ�ͷ�ļ�
#include "GAS/GAS_AbilitySystemComponent.h"
#include "GAS/GAS_AttributeSet.h"
#include "GAS_Character.generated.h"

UCLASS()
class MYBASEGAMEPLAY_API AGAS_Character : public ACharacter, public IAbilitySystemInterface
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
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	TObjectPtr<UGAS_AbilitySystemComponent> GAS_AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UGAS_AttributeSet> GAS_AttributeSet;

};
