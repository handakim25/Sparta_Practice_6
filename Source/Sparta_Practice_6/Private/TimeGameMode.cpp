// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeGameMode.h"

#include "PlatformerPlayerController.h"
#include "PlayerCharacter.h"

ATimeGameMode::ATimeGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = APlatformerPlayerController::StaticClass();
	
	RoundTime = 300.0f;
}

float ATimeGameMode::GetRemainTime() const
{
	return GetWorldTimerManager().IsTimerActive(TimerHandle) ?
		GetWorldTimerManager().GetTimerRemaining(TimerHandle) : 0.0f;
}

void ATimeGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATimeGameMode::OnRoundEnd, RoundTime, false);
}

void ATimeGameMode::OnRoundEnd()
{
	// 패배 처리
	// - 게임 시간 정지
	// - 게임 종료 UI 출력 -> 확인 누르면 레벨 재시작
}
