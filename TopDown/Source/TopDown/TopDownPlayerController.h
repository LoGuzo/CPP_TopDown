// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopDownPlayerController.generated.h"

UCLASS()
class ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATopDownPlayerController();
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	// End PlayerController interface
	
	/** Navigate player to the given world location. */
	UFUNCTION(Server, Reliable)
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	UFUNCTION(Server, Reliable)
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterruped);

	UFUNCTION(Server, Reliable)
	void Attack();

	UFUNCTION(Server, Reliable)
	void AttackAddDynamic();

	UFUNCTION(NetMulticast, Reliable)
	void SeverAttack();

	UPROPERTY(Replicated,VisibleAnywhere)
	bool IsAttacking;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
};


