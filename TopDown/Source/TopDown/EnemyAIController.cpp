// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


AEnemyAIController::AEnemyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("BehaviorTree'/Game/AI/BT_EnemyCharacter.BT_EnemyCharacter'"));
	if (BT.Succeeded())
	{
		EnemyBehaviorTree = BT.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BD(TEXT("BlackboardData'/Game/AI/BB_EnemyCharacter.BB_EnemyCharacter'"));
	if (BD.Succeeded())
	{
		EnemyBlackboradData = BD.Object;
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (UseBlackboard(EnemyBlackboradData, Blackboard))
	{
		if (RunBehaviorTree(EnemyBehaviorTree)) 
		{
			//TODO
		}
	}
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
