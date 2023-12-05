// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Attack.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	bNotifyTick = true;
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (EnemyCharacter == nullptr)
		return EBTNodeResult::Failed;

	EnemyCharacter->Attack();
	blsAttacking = true;

	EnemyCharacter->OnAttackEnd.AddLambda([this]()
		{
			blsAttacking = false;
		});
	return Result;
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (blsAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
