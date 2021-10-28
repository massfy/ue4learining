// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"

#include "Engine/World.h"
#include "Base_Actor.h"

// Sets default values
APawnVolume::APawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	//RootComponent = SpawnBox;

}

FVector APawnVolume::GetSpawnPoint()
{
	FVector Extent = SpawnBox->GetScaledBoxExtent();
	FVector Pos = SpawnBox->GetComponentLocation();
	FVector SpawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(Pos, Extent);
	return SpawnPoint;
}


void APawnVolume::ActorSpawn_Implementation(UClass* MyActor, FVector const& Location)
{
	if (MyActor)
	{
		UWorld* MyWorld=GetWorld();
		if (MyWorld)
		{
			ABase_Actor* Creature = MyWorld->SpawnActor<ABase_Actor>(MyActor, Location, FRotator(0.f));
		}
	}
}

// Called when the game starts or when spawned
void APawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

