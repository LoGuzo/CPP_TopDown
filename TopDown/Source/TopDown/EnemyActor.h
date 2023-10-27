// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class TOPDOWN_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Direc, Meta = (AllowPrivateAccess = true))
	int32 Direc;

public:
	UFUNCTION(BlueprintCallable, Category = "Direc")
	int32 GetDirec() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
