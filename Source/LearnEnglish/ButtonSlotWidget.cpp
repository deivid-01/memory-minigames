// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonSlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

void UButtonSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonSlot->SetBackgroundColor(FColor::MakeRandomColor());
	BtnInitialColor = ButtonSlot->BackgroundColor;
	ButtonSlot->OnClicked.AddDynamic(this,&UButtonSlotWidget::OnSlotClicked);

	
}
void UButtonSlotWidget::OnSlotClicked()
{
	OnClicked.ExecuteIfBound(SlotIndex);
}

void UButtonSlotWidget::Highlight() const
{
	FLinearColor AlphaColor = FLinearColor::White;
	AlphaColor.A = 1;
	ButtonSlot->WidgetStyle.Normal.TintColor = FSlateColor(AlphaColor);
	ThumbnailImage->SetBrushTintColor(FSlateColor(AlphaColor));
	UGameplayStatics::PlaySound2D(this,AnimalNameSound);
	
	
	
}

FLinearColor UButtonSlotWidget::GetInitialBtnColor() const
{
	return BtnInitialColor;
}

void UButtonSlotWidget::ResetColor()
{
	FLinearColor AlphaColor = FLinearColor(.2,.2,.2);
	
	
	ButtonSlot->WidgetStyle.Normal.TintColor = FSlateColor(AlphaColor);
	ThumbnailImage->SetBrushTintColor(FSlateColor( FLinearColor(.3,.3,.3)));
}


