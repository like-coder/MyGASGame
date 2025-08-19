// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAS_Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGAS_Character::AGAS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//��������
	bReplicates = true;
	// �����������ײ����
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GAS_AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>(TEXT("GAS_AbilitySystemComponent"));
	GAS_AttributeSet = CreateDefaultSubobject<UGAS_AttributeSet>(TEXT("GAS_AttributeSet"));

	//���ͷ����Ѫ��UI
	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidgetComponent"));
	OverHeadWidgetComponent->SetupAttachment(GetRootComponent());
}

void AGAS_Character::ServerSideInit()
{
	// ���õ�ǰ��ɫ��ΪOwner��Avatar�����ں�����������Ч��Ӧ��
	GAS_AbilitySystemComponent->InitAbilityActorInfo(this, this);
	GAS_AbilitySystemComponent->ApplyInitialEffects();
	GAS_AbilitySystemComponent->GiveInitialAbilities();
}

void AGAS_Character::ClientSideInit()
{
	// ���õ�ǰ��ɫ��ΪOwner��Avatar�����ں�����������Ч��Ӧ��
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
	ConfigureOverHeadStatusWidget();
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

bool AGAS_Character::IsLocallyControlledByPlayer() const
{
	return GetController() && GetController()->IsLocalPlayerController();
}

void AGAS_Character::ConfigureOverHeadStatusWidget()
{
	if (!OverHeadWidgetComponent)
	{
		return;
	}

	// �����ɫ�ɱ�����ҿ���
	if (IsLocallyControlledByPlayer())
	{
		// ����ͷ��UI���
		OverHeadWidgetComponent->SetHiddenInGame(true);
		return;
	}

	// ��ͷ��UI������û��ؼ�����ת��ΪUOverHeadStatsGauge����
	UOverHeadStatsGauge* OverHeadStatsGauge = Cast<UOverHeadStatsGauge>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (OverHeadStatsGauge)
	{
		// ʹ������ϵͳ�������ͷ��ͳ������
		ConfigureWithASC(GetAbilitySystemComponent(), OverHeadStatsGauge);
		// ��ʾͷ��UI���
		OverHeadWidgetComponent->SetHiddenInGame(false);

		// ���֮ǰ�Ķ�ʱ��,��ֹ�ظ�����
		GetWorldTimerManager().ClearTimer(HeadStatGaugeVisibilityUpdateTimerHandle);
		// �����µĶ�ʱ���������Ե��� UpdateHeadGaugeVisibility ����
		// ���ڳ�������ɫ�����֮��ľ��벢����ͷ��UI�ɼ���״̬
		GetWorldTimerManager().SetTimer(HeadStatGaugeVisibilityUpdateTimerHandle, 
			this, &AGAS_Character::UpdateHeadGaugeVisibility,
			HeadStatGaugeVisibilityCheckUpdateGap, true);
	}
}

void AGAS_Character::ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComponent, UOverHeadStatsGauge* OverHeadStatsGauge)
{
	if (AbilitySystemComponent)
	{
		OverHeadStatsGauge->GetHealthBar()->SetAndBoundToGameplayAttribute(AbilitySystemComponent, UGAS_AttributeSet::GetHealthAttribute(), UGAS_AttributeSet::GetMaxHealthAttribute());
		OverHeadStatsGauge->GetManaBar()->SetAndBoundToGameplayAttribute(AbilitySystemComponent, UGAS_AttributeSet::GetManaAttribute(), UGAS_AttributeSet::GetMaxManaAttribute());
	}
}

// ��ʱ�����õĸ��º�����ʵ��
void AGAS_Character::UpdateHeadGaugeVisibility()
{
	// ��ȡ������ҵ�Pawn��ɫ�����ڼ����뵱ǰ��ɫ�ľ���
	APawn* LocalPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (LocalPlayerPawn)
	{
		// ���㵱ǰ��ɫ�뱾�����֮���ƽ������
		float DistSquared = FVector::DistSquared(GetActorLocation(), LocalPlayerPawn->GetActorLocation());
		// ������볬���趨�Ŀɼ���Χ��������ͷ��״̬�����
		OverHeadWidgetComponent->SetHiddenInGame(DistSquared > HeadStatGaugeVisibilityRangeSquared);
	}
}

