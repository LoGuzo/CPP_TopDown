// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TopHpWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UTopHpWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindHp(class UEnemyStatComponent* _StatComp);

	void UpdateHp();

private:
	TWeakObjectPtr<class UEnemyStatComponent> CStatComponent;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Hp;
};
