// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeGameMode.h"

#include "PlatformerPlayerController.h"
#include "PlayerCharacter.h"

ATimeGameMode::ATimeGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = APlatformerPlayerController::StaticClass();

	StartTime = 0.0f;
	RoundTime = 300.0f;
	RemainTime = 300.0f;
}

float ATimeGameMode::GetRemainTime() const
{
	return RemainTime;
}

void ATimeGameMode::EndGame(const bool bGameClear) const
{
	OnGameEnd.Broadcast(bGameClear);
}

void ATimeGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartTime = GetWorld()->GetTimeSeconds();
	RemainTime = RoundTime;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATimeGameMode::UpdateTimer, 1.0f, true);
}

void ATimeGameMode::UpdateTimer()
{
	if (RemainTime > 0.0f)
	{
		RemainTime--;

		OnTimerUpdated.Broadcast(RemainTime);
	}
	else
	{
		EndGame(false);	
	}
}
