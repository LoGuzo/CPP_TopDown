// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "TopDownCharacter.h"
#include "TopDownAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	IsAttacking = false;
}

void ATopDownPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			if (HasAuthority()) {
				SetNewMoveDestination(Hit.ImpactPoint);
			}
			else {
				SetNewMoveDestination(Hit.ImpactPoint);
				if (!IsAttacking)
				{
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Hit.ImpactPoint);
				}
			}
		}
	}
}

void ATopDownPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATopDownPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ATopDownPlayerController::OnSetDestinationReleased);
	InputComponent->BindAction("Attack", IE_Pressed, this, &ATopDownPlayerController::Attack);
}

void ATopDownPlayerController::BeginPlay()
{
	AttackAddDynamic();
}

void ATopDownPlayerController::SetNewMoveDestination_Implementation(const FVector DestLocation)
{
	if (!IsAttacking)
	{
		APawn* const MyPawn = GetPawn();
		if (MyPawn)
		{
			float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

			// We need to issue move command only if far enough in order for walk animation to play correctly
			if ((Distance > 120.0f))
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
			}
		}
	}
}

void ATopDownPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ATopDownPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ATopDownPlayerController::OnAttackMontageEnded_Implementation(UAnimMontage* Montage, bool bInterruped)
{
	IsAttacking = false;
}
void ATopDownPlayerController::Attack_Implementation()
{
	if (IsAttacking)
		return;
	SeverAttack();
	IsAttacking = true;
}

void ATopDownPlayerController::SeverAttack_Implementation()
{
	ATopDownCharacter* TopDownCharacter = Cast<ATopDownCharacter>(GetPawn());
	
	if (TopDownCharacter) {
		StopMovement();
		TopDownCharacter->AttackMontage();
	}
		
}

void ATopDownPlayerController::AttackAddDynamic_Implementation()
{
	if (ATopDownCharacter* MyPawn = Cast<ATopDownCharacter>(GetPawn()))
	{
		if (UTopDownAnimInstance* AnimInstance = Cast<UTopDownAnimInstance>(MyPawn->GetMesh()->GetAnimInstance()))
		{
			AnimInstance->OnMontageEnded.AddDynamic(this, &ATopDownPlayerController::OnAttackMontageEnded);
		}
	}
}

void ATopDownPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATopDownPlayerController, IsAttacking);
}


