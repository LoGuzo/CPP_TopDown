// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownGameInstance.h"

UTopDownGameInstance::UTopDownGameInstance() {
	static ConstructorHelpers::FObjectFinder<UDataTable>DATA(TEXT("DataTable'/Game/TopDownCPP/Blueprints/Progression/Stat/StatDataTable.StatDataTable'"));

	MyStats = DATA.Object;
}

void UTopDownGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("MyGameInstance %d"), GetStatData(1)->Attack);
}

FStatStruct* UTopDownGameInstance::GetStatData(int32 type)
{
	return MyStats->FindRow<FStatStruct>(*FString::FromInt(type), TEXT(""));
}

void UTopDownGameInstance::setChkXY(float x, float y)
{
	chkX = x;
	chkY = y;
}

void UTopDownGameInstance::setXYPlus(float x, float y)
{
	XPlus = x;
	YPlus = y;
}

void UTopDownGameInstance::setcntEnemyG(bool g)
{
	cntEnemyG = g;
}

void UTopDownGameInstance::setcntEnemyY(bool y)
{
	cntEnemyY = y;
}

void UTopDownGameInstance::setcntEnemyR(bool r)
{
	cntEnemyR = r;
}

void UTopDownGameInstance::setFirstE(bool f)
{
	FirstEnemy = f;
}

void UTopDownGameInstance::addSaveCoordi(const FVector& Coordinate)
{
	saveCoordi.Add(Coordinate);
}

void UTopDownGameInstance::delSaveCoordi(const FVector& Coordinate)
{
	saveCoordi.Remove(Coordinate);
}

bool UTopDownGameInstance::chkSaveCoordi(const FVector& Coordinate)
{
	return saveCoordi.Contains(Coordinate);
}
