// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "TopDownGameInstance.generated.h"

/**
 * 
 */
USTRUCT()
struct FStatStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	int32 type;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	int32 MaxHP;
};
UCLASS()
class TOPDOWN_API UTopDownGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UTopDownGameInstance();

	virtual void Init() override;

	FStatStruct* GetStatData(int32 type);

private:
	UPROPERTY()
	class UDataTable* MyStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Coordi, Meta = (AllowPrivateAccess = true))
	float chkX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Coordi, Meta = (AllowPrivateAccess = true))
	float chkY;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Coordi, Meta = (AllowPrivateAccess = true))
	float XPlus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Coordi, Meta = (AllowPrivateAccess = true))
	float YPlus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Enemy, Meta = (AllowPrivateAccess = true))
	bool cntEnemyG;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Enemy, Meta = (AllowPrivateAccess = true))
	bool cntEnemyY;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Enemy, Meta = (AllowPrivateAccess = true))
	bool cntEnemyR;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Enemy, Meta = (AllowPrivateAccess = true))
	bool FirstEnemy = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Coordi, Meta = (AllowPrivateAccess = true))
	TArray<FVector> saveCoordi;

public:

	UFUNCTION(BlueprintCallable)
	void setChkXY(float x, float y);

	UFUNCTION(BlueprintCallable)
	void setXYPlus(float x, float y);

	UFUNCTION(BlueprintCallable)
	void setcntEnemyG(bool g);

	UFUNCTION(BlueprintCallable)
	void setcntEnemyY(bool y);

	UFUNCTION(BlueprintCallable)
	void setcntEnemyR(bool r);

	UFUNCTION(BlueprintCallable)
	void setFirstE(bool f);

	UFUNCTION(BlueprintCallable)
	void addSaveCoordi(const FVector& Coordinate);

	UFUNCTION(BlueprintCallable)
	void delSaveCoordi(const FVector& Coordinate);

	UFUNCTION(BlueprintCallable)
	bool chkSaveCoordi(const FVector& Coordinate);
};
