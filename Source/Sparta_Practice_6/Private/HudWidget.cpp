// Fill out your copyright notice in the Description page of Project Settings.


#include "HudWidget.h"

#include "TimeGameMode.h"
#include "Components/TextBlock.h"

void UHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto GameMode = GetWorld()->GetAuthGameMode<ATimeGameMode>())
	{
		UpdateTimerDisplay(GameMode->GetRemainTime());
		GameMode->OnTimerUpdated.AddDynamic(this, &UHudWidget::UpdateTimerDisplay);
	}
}

void UHudWidget::UpdateTimerDisplay(const int Time)
{
	if (!TimerText) return;

	const int MinutesRemain = Time/60;
	const int SecondsRemain = Time%60;

	const FString TimerString = FString::Printf(TEXT("%02d:%02d"), MinutesRemain, SecondsRemain);
	TimerText->SetText(FText::FromString(TimerString));
}
