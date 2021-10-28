// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PawnVolume.h"

// Sets default values
ABase_Actor::ABase_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

//ABase_Actor* ABase_Actor::Clone()
//{
//	UWorld* World = GetWorld();
//	FVector Pos = APawnVolume::GetSpawnPoint();
//	ABase_Actor* TEST_Actor = World->SpawnActor<ABase_Actor>(Pos, FRotator::ZeroRotator);
//
//	return  TEST_Actor;
//}

// Called when the game starts or when spawned
void ABase_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

