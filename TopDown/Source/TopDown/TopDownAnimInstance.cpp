// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownAnimInstance.h"

UTopDownAnimInstance::UTopDownAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Mannequin/Animations/Attack_Montage.Attack_Montage'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
}

// Check Velocity and Play Animation
void UTopDownAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();
	if (IsValid(pawn)) {
		Speed = pawn->GetVelocity().Size();
	}
}

//Attack Montage
void UTopDownAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.f);
	}
}
