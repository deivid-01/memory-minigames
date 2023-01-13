// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"

#include "GridGameWidget.h"
#include "WinWidget.h"
#include "LoseWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameMode.h"
void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	GridWidget = Cast<UGridGameWidget>(CreateWidget(this,GridWidgetClass));

	if(!GridWidget) return;
	
	GridWidget->AddToViewport();
	
	GridWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

	GridWidget->OnCompleteHighlight.BindUObject(this ,&AGamePlayerController::StartGame);
	CurrentTotalHighlight = InitialHighlight;
	GridWidget->StartHighLight(CurrentTotalHighlight);
	GridWidget->CheckInput();
	SetShowMouseCursor(true);


}




void AGamePlayerController::StartGame()
{
	
	GridWidget->OnCompleteHighlight.Unbind();
	GridWidget->OnCompleteGame.BindUObject(this,&AGamePlayerController::EndGame);
	GridWidget->SetVisibility(ESlateVisibility::Visible);

	
}

void AGamePlayerController::EndGame(bool bWin)
{

	GridWidget->OnCompleteGame.Unbind();
	GridWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

	if(bWin)
	{
		CurrentTotalHighlight+=1;
		GridWidget->OnCompleteHighlight.BindUObject(this ,&AGamePlayerController::StartGame);
		GridWidget->StartHighLight(CurrentTotalHighlight);
	}
	else
	{
		LoseWidget = Cast<ULoseWidget>(CreateWidget(this,LoseWidgetClass));
		LoseWidget->OnBtnRestartPressed.BindUObject(this,&AGamePlayerController::RestartGame);
		LoseWidget->AddToViewport();
	}	
}

void AGamePlayerController::RestartGame()
{
	if(LoseWidget)
		LoseWidget->OnBtnRestartPressed.Unbind();

	AGameMode* GameMode=Cast<AGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->RestartGame();
}

