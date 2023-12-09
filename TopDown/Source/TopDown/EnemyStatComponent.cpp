// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStatComponent.h"
#include "TopDownGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnemyStatComponent::UEnemyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
	bWantsInitializeComponent = true;
}



// Called when the game starts
void UEnemyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEnemyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetType(type);
}

void UEnemyStatComponent::SetType(int32 newtype)
{
	auto MyGameInstance=Cast<UTopDownGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto StatData = MyGameInstance->GetStatData(newtype);
		if (StatData)
		{
			type = StatData->type;
			Hp = StatData->MaxHP;
			Attack = StatData->Attack;
		}
	}
}

void UEnemyStatComponent::OnAttacked(float DamageAmount)
{
	Hp -= DamageAmount;
	if (Hp < 0)
		Hp = 0;
}

