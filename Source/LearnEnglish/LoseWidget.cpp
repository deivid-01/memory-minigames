// Fill out your copyright notice in the Description page of Project Settings.


#include "LoseWidget.h"

#include "Components/Button.h"

void ULoseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonRestartGame->OnClicked.AddDynamic(this,&ULoseWidget::NotifyBtnPressed);
}

void ULoseWidget::NotifyBtnPressed()
{
	OnBtnRestartPressed.ExecuteIfBound();
}


