// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "HudWidget.h"
#include "ResultWidget.h"
#include "TimeGameMode.h"

APlatformerPlayerController::APlatformerPlayerController()
{
}

void APlatformerPlayerController::ShowResultWidget(bool bClear)
{
	if (ResultWidgetClass)
	{
		if (UResultWidget* ResultWidget = CreateWidget<UResultWidget>(GetWorld(), ResultWidgetClass))
		{
			ResultWidget->AddToViewport();
			
			SetPause(true);
			
			const FInputModeUIOnly InputModeUI;
			SetInputMode(InputModeUI);
			bShowMouseCursor = true;
		}
	}
}

void APlatformerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		UE_LOG(LogTemp, Display, TEXT("Add Mapping Context"));
		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	if (const auto GameMode = GetWorld()->GetAuthGameMode<ATimeGameMode>())
	{
		GameMode->OnGameEnd.AddDynamic(this, &APlatformerPlayerController::ShowResultWidget);
	}

	if (HudWidgetClass)
	{
		HudWidget = CreateWidget<UHudWidget>(this, HudWidgetClass);
		if (HudWidget)
		{
			HudWidget->AddToViewport();
		}
	}
}
