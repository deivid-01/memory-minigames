// Fill out your copyright notice in the Description page of Project Settings.


#include "WinWidget.h"
#include "Components/Button.h"
void UWinWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonRestartGame->OnClicked.AddDynamic(this,&UWinWidget::NotifyBtnPressed);
}

void UWinWidget::NotifyBtnPressed()
{
	OnBtnRestartPressed.ExecuteIfBound();
}
