// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class SPARTA_PRACTICE_6_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Platform")
	class UStaticMeshComponent* Mesh;

	// 상대 좌표 기준으로 이동 목표 지점, Spawn 됬을 때 기준으로 정한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform", meta = (MakeEditWidget))
	FVector TargetLocation;

	// 한 쪽 끝까지 도달하는데 걸리는 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	float Duration;

	// 한 쪽 끝에 도착하고 대기하는 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	float WaitTime;

	// 플랫폼이 움직이고 있는지 여부, 도착지점에서 Wait하는 도중도 True이다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	bool bIsMoving;

	// Spawn 됬을 때의 Target Location
	FVector WorldTargetLocation;
	// Current Alpha
	float CurrentAlpha;
	// 이동 방향, 1.0이면 Start->Target, -1.0이면 Target->Start
	float CurrentDirection;

	// 한쪽 끝에 도달했는지 여부
	bool HasReached() const;
	float CalculateRemainAlpha(float Alpha);
	void StartWaitTimer(float FinalWaitTime);
	
	// 대기 타이머 종료 콜백
	void OnWaitTimerCompleted();
	
private:
	// 시작 지점 표시
	UPROPERTY(VisibleInstanceOnly, Transient, DuplicateTransient, Category = "Platform")
	FVector StartLocation;

	// 한쪽 끝에 도달해서 대기 중인 상태
	bool bIsWaiting;
	FTimerHandle WaitTimerHandle;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
