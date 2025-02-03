// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_PRACTICE_6_API ATimeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATimeGameMode();
	
	UFUNCTION(BlueprintCallable)
	float GetRemainTime() const;
	
protected:
	UPROPERTY(EditAnywhere)
	float RoundTime;
	FTimerHandle TimerHandle;

	virtual void BeginPlay() override;
	void OnRoundEnd();

	// Win UI, Lose UI
};
