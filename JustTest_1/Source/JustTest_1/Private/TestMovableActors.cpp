// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMovableActors.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Base_Weapon.h"

#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"

// Sets default values
ATestMovableActors::ATestMovableActors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));

	RootComponent = BoxComp;

	MeshComp->SetupAttachment(RootComponent);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ATestMovableActors::OnOverlapBegin);

}

void ATestMovableActors::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	StartLoc = GetActorLocation();
	if (OtherActor)
	{
		ABase_Weapon* Weapon = Cast<ABase_Weapon>(OtherActor);
		if (Weapon)
		{
			HittedWeapon = Weapon;
			Weapon->MovableActorSpeed = Speed;
			Weapon->isFlying = false;

			if (Weapon->CurrentWeaponNum == EWeaponW::EW_Weapon1)
			{
				Direction = UPP;
			}
			else if (Weapon->CurrentWeaponNum == EWeaponW::EW_Weapon2)
			{
				Weapon->FourDirCalculate();
				Direction = Weapon->AxesV;
				//Direction = RIGHT;
			}
			else
			{
				Weapon->FourDirCalculate();
				Direction = (Weapon->AxesV)*-1;
				//Direction = FVector(0, 0, 0);
				//Direction = FORWORD;
			}
			Weapon->MovableDir = Direction;
			Weapon->HitWall(this);
			isMoving = true;
			
		}
	}
}

void ATestMovableActors::MeshMove(FVector Dir)
{
	Dir.Normalize(0.0001);

	FVector ChangedLocation = Dir * ((GetWorld()->GetDeltaSeconds()) * Speed);
	FVector TmpLocation = GetActorLocation() + ChangedLocation;

	SetActorLocation(TmpLocation);
}

void ATestMovableActors::StopDetection()
{
	FVector TmpLocation = GetActorLocation();
	float MovDis = TmpLocation.Distance(TmpLocation, StartLoc);
	if (MovDis >= MaxDistance)
	{
		if (HittedWeapon)
		{
			HittedWeapon->DestroyWeapon();
			HittedWeapon = NULL;
		}
		isMoving = false;
	}
}

// Called when the game starts or when spawned
void ATestMovableActors::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestMovableActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isMoving)
	{
		StopDetection();
		MeshMove(Direction);
	}

}

