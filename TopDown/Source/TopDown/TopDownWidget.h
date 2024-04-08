// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TopDownWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_API UTopDownWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindHp(class UEnemyStatComponent* _StatComp);

	void UpdateHp();

	void BindBuff(class ATopDownCharacter* _Character);

	void UpdateBuff();
private:
	TWeakObjectPtr<class UEnemyStatComponent> CStatComponent;

	TWeakObjectPtr<class ATopDownCharacter> CCharacter;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* PB_Hp;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Mp;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Buff;

};
