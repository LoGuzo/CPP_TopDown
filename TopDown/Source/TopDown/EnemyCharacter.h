// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class TOPDOWN_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Called Attack Func
	void Attack();

	void AttackCheck();

	FOnAttackEnd OnAttackEnd;
	// Called OnAttackMontageEnded Func
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterruped);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Hp;

	//Enemy Type
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Type;

	//Enemy Stat
	UPROPERTY(VisibleAnywhere)
	class UEnemyStatComponent* Stat;

	//Enemy Speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(VisibleAnywhere)
	bool IsAttacking = false;

	UPROPERTY()
	class UTopDownAnimInstance* AnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Coordi, Meta = (AllowPrivateAccess = true))
	FVector Coordi;

public:
	UFUNCTION(BlueprintCallable)
	void setCoordi(const FVector& NewCoordi);

	void DestroyC();
};
