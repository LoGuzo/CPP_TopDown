// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TopDownAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHit);
/**
 * 
 */
UCLASS()
class TOPDOWN_API UTopDownAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UTopDownAnimInstance();

	//UTopDownAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	//Called AttackMontage
	void EPlayAttackMontage();
	void CPlayAttackMontage();
	
	//DeadMontage
	void PlayDeadMontage();

	FOnAttackHit OnAttackHit;
	UFUNCTION()
	void setIsDead(bool a);
private:
	//Check Speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float Speed;

	//Enemy AttackMontage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* EAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* CAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DeadCheck, Meta = (AllowPrivateAccess = true))
	bool isDead;

	UFUNCTION()
	void AnimNotify_AttackHit();
};
