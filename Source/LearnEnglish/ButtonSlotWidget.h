// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridGameWidget.h"
#include "Blueprint/UserWidget.h"
#include "ButtonSlotWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FOnClickedEvent,int32 slotIndex);
class UImage;
UCLASS()
class LEARNENGLISH_API UButtonSlotWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnSlotClicked();
public:
	FOnClickedEvent OnClicked;
	void Highlight() const;
	
	FLinearColor GetInitialBtnColor() const;
	
	void SetSlotIndex(int32 slotIndex) 
	{
		this->SlotIndex = slotIndex;
	}

	void ResetColor();


private:
	int32 SlotIndex;
	UPROPERTY( meta=(BindWidget))
	class UButton* ButtonSlot;
	UPROPERTY( meta=(BindWidget))
	UImage* ThumbnailImage;
	UPROPERTY( meta=(BindWidget))
	FLinearColor BtnInitialColor;

	UPROPERTY(EditAnywhere)
	USoundBase* AnimalNameSound;

};
