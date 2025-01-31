// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform.generated.h"

UCLASS()
class SPARTA_PRACTICE_6_API ARotatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// EditAnywhere를 하면 UStaticMeshComponent 자체를 수정할 수 있다.
	// 하지만, 이 클래스가 동작하려면 반드시 UStaticMeshComponent가 필요하므로 VisibleAnywhere로 선언해야 한다.
	// 포인터적으로 생각하면 된다. EditAnywhere은 이중 포인터로 포인터의 값을 변경할 수 있는 것이고 VisibleAnywhere은 UStaticMeshComponent* const Mesh라고 생각하면 된다.
	// 비슷한 코드를 참고하려면 Character.h를 참조

	UPROPERTY(Category="Platform", VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(Category="Platform", EditAnywhere, BlueprintReadWrite)
	FRotator Rotator;

	UPROPERTY(Category="Platform", EditAnywhere, BlueprintReadWrite)
	bool bIsActivated;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
