// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAS_Character.h"

// Sets default values
AGAS_Character::AGAS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//开启复制
	bReplicates = true;
	// 禁用网格的碰撞功能
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GAS_AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>(TEXT("GAS_AbilitySystemComponent"));
	GAS_AttributeSet = CreateDefaultSubobject<UGAS_AttributeSet>(TEXT("GAS_AttributeSet"));

}

void AGAS_Character::ServerSideInit()
{
	// 设置当前角色作为Owner和Avatar，用于后续的能力和效果应用
	GAS_AbilitySystemComponent->InitAbilityActorInfo(this, this);
	GAS_AbilitySystemComponent->ApplyInitialEffects();
}

void AGAS_Character::ClientSideInit()
{
	// 设置当前角色作为Owner和Avatar，用于后续的能力和效果应用
	GAS_AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AGAS_Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController && !NewController->IsPlayerController())
	{
		ServerSideInit();
	}
}

// Called when the game starts or when spawned
void AGAS_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGAS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGAS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AGAS_Character::GetAbilitySystemComponent() const
{
	return GAS_AbilitySystemComponent;
}

