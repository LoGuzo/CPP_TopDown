// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

AEnemyAIController::AEnemyAIController()
{

}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//GetWorld->GetTimerManager().SetTimer(TimerHandle.this)
}

void AEnemyAIController::OnUnPossess()
{
}
