// Fill out your copyright notice in the Description page of Project Settings.


#include "GridGameWidget.h"
#include "ButtonSlotWidget.h"
#include "Math/UnrealMathUtility.h"
#include "Components/TextBlock.h"
void UGridGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TimerManager = &GetWorld()->GetTimerManager();
	SetButtonsArray();
}


void UGridGameWidget::SetButtonsArray()
{
	GridButtons = {ButtonSlot_1, ButtonSlot_2, ButtonSlot_3, ButtonSlot_4};

	for (int i = 0; i < GridButtons.Num(); i++)	
	{
		GridButtons[i]->SetSlotIndex(i);
	}
}


void UGridGameWidget::StartHighLight(int32 TotalHighLight)
{
	HighlightTotal = TotalHighLight;

	if(TotalIndexPatternQueue.Num()>0)
	{
		IndexPatternQueue.Empty();
		for(int32 Index : TotalIndexPatternQueue)
		{
			IndexPatternQueue.Enqueue(Index);
		}
	}
		
	
	HighLightCount = 0;
	TextMsg->SetText(FText::FromString("Memorize the pattern!"));
	TimerManager->SetTimer(HighlightTimerHandler,this,&UGridGameWidget::ChangeBackgroundColor,HighlightSpeedInSeconds,true,3);
}

void UGridGameWidget::CheckInput()
{
	for( UButtonSlotWidget* ButtonSlot : GridButtons)
	{
		ButtonSlot->OnClicked.BindUObject(this,&UGridGameWidget::CheckIndexPattern);
	}
}



void UGridGameWidget::ChangeBackgroundColor()
{
	TextMsg->SetText(FText::FromString("..."));
	if(CurrentHighlightBtn)
	{
		CurrentHighlightBtn->ResetColor();
		CurrentHighlightBtn = nullptr;
		HighLightCount++;
		
		if (  HighLightCount < HighlightTotal ) return;
		
		TimerManager->ClearTimer(HighlightTimerHandler);
		TextMsg->SetText(FText::FromString(""));
		OnCompleteHighlight.ExecuteIfBound();
		
	}
	else
	{
		int32 TargetIndex;
		if(HighLightCount < TotalIndexPatternQueue.Num())
		{
				TargetIndex = TotalIndexPatternQueue[HighLightCount];
		}
		else
		{
			const int32 RandomIndex = FMath::RandRange(0,GridButtons.Num()-1);
			TotalIndexPatternQueue.Add(RandomIndex);
			IndexPatternQueue.Enqueue(RandomIndex);

			TargetIndex = RandomIndex;
		}
		//Create new index
	


		CurrentHighlightBtn = GridButtons[TargetIndex];
		CurrentHighlightBtn->Highlight();
	}
}

void UGridGameWidget::StopTimer()
{
	TimerManager->ClearTimer(HighlightTimerHandler);
}

void UGridGameWidget::CheckIndexPattern(int32 IndexPattern)
{
	if(IndexPatternQueue.IsEmpty()) return;
	
	if(*IndexPatternQueue.Peek()  != IndexPattern)
	{
		OnCompleteGame.ExecuteIfBound(false);
		return;
	}

	IndexPatternQueue.Pop();
	
	if(IndexPatternQueue.IsEmpty())
	{
		OnCompleteGame.ExecuteIfBound(true);
	}
}