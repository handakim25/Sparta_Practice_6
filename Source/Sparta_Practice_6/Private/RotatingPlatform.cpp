// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPlatform.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ARotatingPlatform::ARotatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if(DefaultMeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(DefaultMeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterialAsset(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	if (DefaultMaterialAsset.Succeeded())
	{
		Mesh->SetMaterial(0, DefaultMaterialAsset.Object);
	}
	
	bIsActivated = true;
}

// Called when the game starts or when spawned
void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsActivated && !Rotator.IsNearlyZero())
	{
		FRotator DeltaRotator = Rotator * DeltaTime;
		AddActorLocalRotation(DeltaRotator);
	}
}

