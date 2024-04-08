// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownWidget.h"
#include "EnemyStatComponent.h"
#include "TopDownCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UTopDownWidget::BindHp(class UEnemyStatComponent* _StatComp)
{
	CStatComponent = _StatComp;
	_StatComp->OnHpChanged.AddUObject(this, &UTopDownWidget::UpdateHp);
}

void UTopDownWidget::UpdateHp()
{
	if (CStatComponent.IsValid())
		PB_Hp->SetPercent(CStatComponent->GetHpRatio());
}

void UTopDownWidget::BindBuff(class ATopDownCharacter* _Character)
{
	CCharacter = _Character;
	_Character->OnBuffChanged.AddUObject(this, &UTopDownWidget::UpdateBuff);
	UE_LOG(LogTemp, Warning, TEXT("TTTT"));
}

void UTopDownWidget::UpdateBuff()
{
	if (CCharacter.IsValid()) {
		FString IntegerAsString = FString::FromInt(CCharacter->GetBuff());
		FText NewText = FText::FromString(IntegerAsString);

		Text_Buff->SetText(NewText);
	}
}
