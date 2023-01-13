// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WinWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FOnBtnRestarPressed)
UCLASS()
class LEARNENGLISH_API UWinWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	
public:
	FOnBtnRestarPressed OnBtnRestartPressed;
private:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	class UButton* ButtonRestartGame;
	UFUNCTION()
	void NotifyBtnPressed(); 
};
