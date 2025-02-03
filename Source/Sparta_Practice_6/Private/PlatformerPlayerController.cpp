// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerPlayerController.h"
#include "EnhancedInputSubsystems.h"

APlatformerPlayerController::APlatformerPlayerController()
{
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
}
