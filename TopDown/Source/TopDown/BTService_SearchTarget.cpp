// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "EnemyAIController.h"
#include "TopDownCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_SearchTarget::UBTService_SearchTarget() 
{
	NodeName = TEXT("SearchTarget");
	Interval = 3.0f;
}

// Tick Search
void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return;
	UWorld* World = CurrentPawn->GetWorld();
	FVector Center = CurrentPawn->GetActorLocation();
	float SearchRadius = 500.f;

	if (World == nullptr)
		return;

	TArray<FOverlapResult>OverlapResults;
	FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel5,
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams);

	if (bResult)
	{
		for (auto& OverlapResult : OverlapResults) {
			ATopDownCharacter* TopDownCharacter = Cast<ATopDownCharacter>(OverlapResult.GetActor());
			if (TopDownCharacter && TopDownCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), TopDownCharacter);
				DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);
				return;
			}
		}
		
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
	}
	DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
}