// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */


class UUserWidget;
UCLASS()
class LEARNENGLISH_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	void RestartGame();
	void EndGame(bool bWin);
	void StartGame();
private:
	UPROPERTY(EditAnywhere)
	int32 InitialHighlight;

	int32 CurrentTotalHighlight;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GridWidgetClass;
	UPROPERTY(EditAnywhere)
    	TSubclassOf<UUserWidget> WinWidgetClass;
    UPROPERTY(EditAnywhere)
        TSubclassOf<UUserWidget> LoseWidgetClass;

	class UGridGameWidget* GridWidget;
	class UWinWidget* WinWidget;
	class ULoseWidget* LoseWidget;
};
