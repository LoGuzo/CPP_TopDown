// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "TopDownAnimInstance.h"
#include "TopDownCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyStatComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Stat = CreateDefaultSubobject<UEnemyStatComponent>(TEXT("STAT"));

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Stat->SetType(Type);
	AnimInstance = Cast<UTopDownAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) 
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AEnemyCharacter::OnAttackMontageEnded);
		AnimInstance->OnAttackHit.AddUObject(this, &AEnemyCharacter::AttackCheck);
		AnimInstance->setIsDead(false);
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Attack Func
void AEnemyCharacter::Attack()
{
	if (IsAttacking)
		return;
	auto Animinstance = Cast<UTopDownAnimInstance>(GetMesh()->GetAnimInstance());
	if (Animinstance)
	{
		Animinstance->EPlayAttackMontage();
	}
	IsAttacking = true;
}

void AEnemyCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 100.f;
	float AttackRadius = 50.f;
	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel5,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);
	if (bResult && HitResult.Actor.IsValid())
	{
		FDamageEvent DamageEvent;
		HitResult.Actor->TakeDamage(Stat->GetAttack(), DamageEvent, GetController(), this);
	}

}

void AEnemyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterruped)
{
	IsAttacking = false;
	OnAttackEnd.Broadcast();
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Stat->OnAttacked(DamageAmount);
	Hp = Stat->GetHp();
	if (Hp <= 0) {
		auto Animinstance = Cast<UTopDownAnimInstance>(GetMesh()->GetAnimInstance());
		WhoDestroyed = DamageCauser;
		if (Animinstance)
		{
			Animinstance->PlayDeadMontage();
			Animinstance->setIsDead(true);
			FTimerHandle TimerHandle;
			FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemyCharacter::DestroyC);

			//Delay 1sec
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, false);
		}
	}
	return DamageAmount;
}

void AEnemyCharacter::setCoordi(const FVector& NewCoordi)
{
	Coordi = NewCoordi;
}

void AEnemyCharacter::DestroyC()
{
	Destroy();
}


