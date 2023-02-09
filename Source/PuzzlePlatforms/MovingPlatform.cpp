// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);

	MPM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MPM"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));

	RootComponent = MPM;

	if (Cube.Succeeded())
	{
		MPM->SetStaticMesh(Cube.Object);
	}
	
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		if (Location.X >= 400.f)
			Speed = -50.f;
		else if (Location.X <= 0.f)
			Speed = 50.f;
		Location += FVector(Speed * DeltaTime, 0, 0);
		SetActorLocation(Location);
		UE_LOG(LogTemp, Display, TEXT("X : %f"), Location.X);
	}
	
}
