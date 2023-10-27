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

	//UTopDownAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float Speed;
};
