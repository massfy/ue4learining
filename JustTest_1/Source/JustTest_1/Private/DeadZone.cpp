// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadZone.h"
#include "Components/BoxComponent.h"
#include "Base_Character.h"

// Sets default values
ADeadZone::ADeadZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeadZone = CreateDefaultSubobject<UBoxComponent>(TEXT("DeadZone"));
	RootComponent = DeadZone;

	DeadZone->OnComponentBeginOverlap.AddDynamic(this, &ADeadZone::OnOverlapBegin);
}

void ADeadZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, TEXT("aaaaaaaaaaaaaaaaaaaa"));
	if (OtherActor)
	{
		ABase_Character* Man = Cast<ABase_Character>(OtherActor);
		if (Man)
		{
			Man->CharacterDead();
		}
	}
}

// Called when the game starts or when spawned
void ADeadZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeadZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

