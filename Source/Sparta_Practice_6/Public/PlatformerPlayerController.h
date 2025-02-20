// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "PlatformerPlayerController.generated.h"

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class SPARTA_PRACTICE_6_API APlatformerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APlatformerPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputAction> LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputAction> JumpAction;

	UFUNCTION(BluePrintCallable, Category = "UI")
	void ShowResultWidget(bool bClear);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UHudWidget> HudWidgetClass;
	UPROPERTY()
	TObjectPtr<class UHudWidget> HudWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UResultWidget> ResultWidgetClass;
};
