// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TopDownAnimInstance.generated.h"

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
	void PlayAttackMontage();
private:
	//Check Speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float Speed;

	//Enemy AttackMontage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
};
