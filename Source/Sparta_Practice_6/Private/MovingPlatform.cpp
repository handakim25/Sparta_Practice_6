// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootScene);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootScene);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (DefaultMeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(DefaultMeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterialAsset(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (DefaultMaterialAsset.Succeeded())
	{
		Mesh->SetMaterial(0, DefaultMaterialAsset.Object);
	}

	TargetLocation = FVector::ZeroVector;
	bIsMoving = true;
	WaitTime = 0.0f;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	CurrentAlpha = 0.0f;
	CurrentDirection = 1.0f;
	WorldTargetLocation = StartLocation + TargetLocation;
}

bool AMovingPlatform::HasReached() const
{
	return CurrentAlpha >= 1.0f || CurrentAlpha <= 0.0f;
}

float AMovingPlatform::CalculateRemainAlpha(const float Alpha)
{
	if (Alpha < 0.0f)
	{
		return FMath::Abs(Alpha);
	}
	else if (Alpha > 1.0f)
	{
		return 2.0f - Alpha;
	}
	else
	{
		return Alpha;
	}
}

void AMovingPlatform::StartWaitTimer(float FinalWaitTime)
{
	if (bIsMoving)
	{
		GetWorldTimerManager().ClearTimer(WaitTimerHandle);
	}
	
	bIsWaiting = true;
	GetWorldTimerManager().SetTimer(WaitTimerHandle, this, &AMovingPlatform::OnWaitTimerCompleted, FinalWaitTime, false);
}

void AMovingPlatform::OnWaitTimerCompleted()
{
	bIsWaiting = false;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsMoving)
	{
		return;
	}
	// Timer가 깨워줄 때까지 기다린다.
	if (bIsWaiting)
	{
		return;
	}
	
	// Duration이 길어질수록 DeltaTime이 천천히 차야 되고 짧으면 빨리 차게 된다.
	// CurrentAlpha만 계산해주면 최종 Lerp 연산으로 위치를 계산하게 된다.
	CurrentAlpha += DeltaTime / Duration * CurrentDirection;
	
	// 너무 빠른 움직임은 제대로 계산될 수 없다. 그러한 상황은 추가적인 로직이 필요하므로 현재로는 안전하게 작동할 수 있도록 구현해 둔다.
	CurrentAlpha = FMath::Clamp(CurrentAlpha, -1.0f, 2.0f);
	if (HasReached())
	{
		// 방향은 항상 바꿔준다. Wait Timer는 종료 후에 그대로 이동만 하면 된다.
		CurrentDirection *= -1.0f;
		
		// Wait Time이 존재할 경우 종점에 위치하게 한다. 그 후에 초과된 시간만큼 시간을 대기 시간에서 빼고 계산된 대기 시간만큼 대기를 한다.
		if (WaitTime > 0.0f)
		{
			// Get Remain Time, 비율을 위해 시간을 Duration으로 나누었듯이 비율에 Duration을 곱하면 시간이 된다.
			float RemainTime = CalculateRemainAlpha(CurrentAlpha) * Duration;
			CurrentAlpha = FMath::Clamp(CurrentAlpha, 0.0f, 1.0f);
			
			// Wait Time을 계산해서 Wait 진행
			if (WaitTime - RemainTime > 0.0f)
			{
				StartWaitTimer(WaitTime - RemainTime);
			}
		}
		// Wait Time이 존재하지 않을 경우 종점을 치고 지나간다. 초과된 기간만큼 새로운 거리를 계산한다.
		else
		{
			// -0.2 -> 0.2
			// 1.2 -> 0.8
			CurrentAlpha = CalculateRemainAlpha(CurrentAlpha);
		}
	}

	// Ease를 적용하게 된다면 방향을 적용해야 할 수도 있다. 해당 부분은 추후에 구현
	FVector NewLocation = FMath::Lerp(StartLocation, WorldTargetLocation, CurrentAlpha);
	SetActorLocation(NewLocation);
}

