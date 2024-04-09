// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "TopDownAnimInstance.h"
#include "TopDownCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyStatComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Components/WidgetComponent.h"
#include "TopHpWidget.h"

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
	IsAttacking = false;

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget>UW(TEXT("WidgetBlueprint'/Game/TopDownCPP/Blueprints/UI/BP_TopHp.BP_TopHp_C'"));
	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 500.f));
	}
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Stat->SetType(Type);
	AttackAddDynamic();
}

void AEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInstance = Cast<UTopDownAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance) 
	{
		AnimInstance->OnAttackHit.AddUObject(this, &AEnemyCharacter::AttackCheck);
		AnimInstance->setIsDead(false);
	}
	HpBar->InitWidget();

	HpWidget = Cast<UTopHpWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(Stat);
		HpWidget->SetRenderOpacity(0.f);
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
void AEnemyCharacter::OnAttackMontageEnded_Implementation(UAnimMontage* Montage, bool bInterruped)
{
	IsAttacking = false;
}
void AEnemyCharacter::Attack_Implementation()
{
	if (IsAttacking)
		return;
	SeverAttack();
	IsAttacking = true;
}

void AEnemyCharacter::SeverAttack_Implementation()
{
	AnimInstance = Cast<UTopDownAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->EPlayAttackMontage();
	}
}

void AEnemyCharacter::AttackAddDynamic_Implementation()
{
	AnimInstance = Cast<UTopDownAnimInstance>(GetMesh()->GetAnimInstance());
	if(AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AEnemyCharacter::OnAttackMontageEnded);
	}
}

void AEnemyCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEnemyCharacter, IsAttacking);
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Stat->OnAttacked(DamageAmount);
	Hp = Stat->GetHp();
	HpWidget->SetRenderOpacity(1.f);
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


