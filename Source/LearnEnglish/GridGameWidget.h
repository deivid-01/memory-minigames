// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"

#include "GameFramework/GameMode.h"

#include "GridGameWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FOncompleteHighlight)
DECLARE_DELEGATE_OneParam(FOncompleteGame,bool bWin);


class UButtonSlotWidget;
UCLASS()
class LEARNENGLISH_API UGridGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;
public:
	FOncompleteHighlight OnCompleteHighlight;
	FOncompleteGame OnCompleteGame;
	void StartHighLight(int32 TotalHighLight);
	void CheckInput();


	
private:
	UPROPERTY(EditAnywhere)
	float HighlightSpeedInSeconds;

	int32 HighlightTotal;	
	int32 HighLightCount;
	
	UPROPERTY( meta=(BindWidget))
	UButtonSlotWidget* ButtonSlot_1;
	UPROPERTY( meta=(BindWidget))
	UButtonSlotWidget* ButtonSlot_2;
	UPROPERTY( meta=(BindWidget))
	UButtonSlotWidget* ButtonSlot_3;
	UPROPERTY( meta=(BindWidget))
	UButtonSlotWidget* ButtonSlot_4;
	UPROPERTY( meta=(BindWidget))
	UImage* BackgroundImage;
	UPROPERTY()
	TArray<UButtonSlotWidget*> GridButtons;
	UPROPERTY()
	UButtonSlotWidget* CurrentHighlightBtn;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextMsg;
		
	FTimerManager* TimerManager;
	FTimerHandle HighlightTimerHandler;
	
	TQueue<int32>IndexPatternQueue;
	TArray<int32>TotalIndexPatternQueue;
	
	
	void SetButtonsArray();
	void ChangeBackgroundColor();
	void StopTimer();
	void CheckIndexPattern(int32 IndexPattern);
};
