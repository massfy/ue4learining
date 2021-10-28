// Fill out your copyright notice in the Description page of Project Settings.


#include "NextLevelVolume.h"
#include"Base_Character.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
ANextLevelVolume::ANextLevelVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Volume = CreateDefaultSubobject<UBoxComponent>("Volume");
	RootComponent = Volume;

	NextLevel = "two";

}

void ANextLevelVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ABase_Character* Man = Cast<ABase_Character>(OtherActor);
		if (Man)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				FName CurrentLevel(*World->GetMapName());
				if (CurrentLevel != NextLevel)
				{
					UGameplayStatics::OpenLevel(World, NextLevel);
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ANextLevelVolume::BeginPlay()
{
	Super::BeginPlay();
	Volume->OnComponentBeginOverlap.AddDynamic(this, &ANextLevelVolume::OnOverlapBegin);


}

// Called every frame
void ANextLevelVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

