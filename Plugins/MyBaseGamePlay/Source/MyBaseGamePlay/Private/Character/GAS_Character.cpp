// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GAS_Character.h"
#include "Kismet/GameplayStatics.h"

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

	//添加头部的血条UI
	OverHeadWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverHeadWidgetComponent"));
	OverHeadWidgetComponent->SetupAttachment(GetRootComponent());
}

void AGAS_Character::ServerSideInit()
{
	// 设置当前角色作为Owner和Avatar，用于后续的能力和效果应用
	GAS_AbilitySystemComponent->InitAbilityActorInfo(this, this);
	GAS_AbilitySystemComponent->ApplyInitialEffects();
	GAS_AbilitySystemComponent->GiveInitialAbilities();
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

	// 如果角色由本地玩家控制
	if (IsLocallyControlledByPlayer())
	{
		// 隐藏头顶UI组件
		OverHeadWidgetComponent->SetHiddenInGame(true);
		return;
	}

	// 将头顶UI组件的用户控件对象转换为UOverHeadStatsGauge类型
	UOverHeadStatsGauge* OverHeadStatsGauge = Cast<UOverHeadStatsGauge>(OverHeadWidgetComponent->GetUserWidgetObject());
	if (OverHeadStatsGauge)
	{
		// 使用能力系统组件配置头顶统计量表
		ConfigureWithASC(GetAbilitySystemComponent(), OverHeadStatsGauge);
		// 显示头顶UI组件
		OverHeadWidgetComponent->SetHiddenInGame(false);

		// 清除之前的定时器,防止重复调用
		GetWorldTimerManager().ClearTimer(HeadStatGaugeVisibilityUpdateTimerHandle);
		// 设置新的定时器，周期性调用 UpdateHeadGaugeVisibility 方法
		// 用于持续检测角色与玩家之间的距离并更新头顶UI可见性状态
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

// 定时器调用的更新函数的实现
void AGAS_Character::UpdateHeadGaugeVisibility()
{
	// 获取本地玩家的Pawn角色，用于计算与当前角色的距离
	APawn* LocalPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (LocalPlayerPawn)
	{
		// 计算当前角色与本地玩家之间的平方距离
		float DistSquared = FVector::DistSquared(GetActorLocation(), LocalPlayerPawn->GetActorLocation());
		// 如果距离超过设定的可见范围，则隐藏头顶状态条组件
		OverHeadWidgetComponent->SetHiddenInGame(DistSquared > HeadStatGaugeVisibilityRangeSquared);
	}
}

