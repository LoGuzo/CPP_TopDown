// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownAnimInstance.h"
#include <TopDown/TopDownPlayerController.h>

UTopDownAnimInstance::UTopDownAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Mannequin/Animations/Attack_Montage.Attack_Montage'"));
	if (AM.Succeeded())
	{
		EAttackMontage = AM.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> CAM(TEXT("AnimMontage'/Game/Mannequin/Animations/TopDown_AttackMontage.TopDown_AttackMontage'"));
	if (CAM.Succeeded())
	{
		CAttackMontage = CAM.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DAM(TEXT("AnimMontage'/Game/Mannequin/Animations/Die_Montage.Die_Montage'"));
	if (DAM.Succeeded())
	{
		DeadMontage = DAM.Object;
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
void UTopDownAnimInstance::EPlayAttackMontage()
{
	if (!Montage_IsPlaying(EAttackMontage))
	{
		Montage_Play(EAttackMontage, 1.f);
	}
}

void UTopDownAnimInstance::CPlayAttackMontage()
{
	if (!Montage_IsPlaying(CAttackMontage))
	{
		Montage_Play(CAttackMontage, 1.f);
	}
}

void UTopDownAnimInstance::PlayDeadMontage()
{
	if (!Montage_IsPlaying(DeadMontage))
	{
		Montage_Play(DeadMontage, 1.f);
	}
}

void UTopDownAnimInstance::setIsDead(bool a)
{
	isDead = a;
}

void UTopDownAnimInstance::AnimNotify_AttackHit()
{
	OnAttackHit.Broadcast();
}
