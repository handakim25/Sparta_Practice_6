// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerUpdated, int, Seconds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameEnd, bool, GameClear);

/**
 * 
 */
UCLASS()
class SPARTA_PRACTICE_6_API ATimeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATimeGameMode();
	
	UPROPERTY(BlueprintAssignable)
	FOnTimerUpdated OnTimerUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnGameEnd OnGameEnd;
	
	UFUNCTION(BlueprintCallable)
	float GetRemainTime() const;
	
	void EndGame(bool bGameClear) const;

protected:
	// 1라운드 제한 시간
	UPROPERTY(EditAnywhere)
	float RoundTime;
	// 남은 시간
	float RemainTime;
	// 시작 시간
	float StartTime;
	FTimerHandle TimerHandle;
	
	virtual void BeginPlay() override;

	void UpdateTimer();
};
