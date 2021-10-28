// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableActors.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Base_Weapon.h"

#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

// Sets default values
AMovableActors::AMovableActors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));

	RootComponent = MeshComp;

	BoxComp->SetupAttachment(MeshComp);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AMovableActors::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AMovableActors::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovableActors::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, TEXT("aaaaaaaaaaaaaaaaaaaa"));
	
	if (OtherActor)
	{
		ABase_Weapon* Weapon = Cast<ABase_Weapon>(OtherActor);
		if (Weapon)
		{
			isMoving = true;
			if (Weapon->CurrentWeaponNum == EWeaponW::EW_Weapon1)
			{
				Direction = UPP;
			}
			else if (Weapon->CurrentWeaponNum == EWeaponW::EW_Weapon2)
			{
				Direction = RIGHT;
			}
			else
			{
				Direction = FORWORD;
			}
		}
	}
}

void AMovableActors::MeshMove( FVector Dir)
{
	Dir.Normalize(0.0001);

	FVector ChangedLocation = Dir * ((GetWorld()->GetDeltaSeconds()) * Speed);
	FVector TmpLocation = GetActorLocation() + ChangedLocation;

	SetActorLocation(TmpLocation);
}

// Called every frame
void AMovableActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(isMoving)
	{
		MeshMove(Direction);
	}
	
}

