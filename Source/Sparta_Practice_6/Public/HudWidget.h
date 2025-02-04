// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_PRACTICE_6_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateTimerDisplay(int Time);
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimerText;
};
