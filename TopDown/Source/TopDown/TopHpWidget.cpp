// Fill out your copyright notice in the Description page of Project Settings.


#include "TopHpWidget.h"
#include "EnemyStatComponent.h"
#include "Components/ProgressBar.h"

void UTopHpWidget::BindHp(class UEnemyStatComponent* _StatComp)
{
	CStatComponent = _StatComp;
	_StatComp->OnHpChanged.AddUObject(this, &UTopHpWidget::UpdateHp);
}

void UTopHpWidget::UpdateHp()
{
	if (CStatComponent.IsValid())
		PB_Hp->SetPercent(CStatComponent->GetHpRatio());
}