// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Weapon.h"
#include "Base_Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Base_Character.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "MovableActors.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABase_Weapon::ABase_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	
	

	ColliBOX = CreateDefaultSubobject<UBoxComponent>(TEXT("ColliBOX"));
	//CollBOX->SetupAttachment(RootComponent);
	RootComponent = ColliBOX;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	//RootComponent = MeshComp;

	ColliBOX->SetNotifyRigidBodyCollision(true);
	ColliBOX->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	ColliBOX->SetGenerateOverlapEvents(true);
	ColliBOX->BodyInstance.SetInstanceNotifyRBCollision(true);
	ColliBOX->OnComponentHit.AddDynamic(this, &ABase_Weapon::OnHit);

	WeaponMoves = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("WeaponMoves"));

	ColliBOX->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//武器移动具体参数
	WeaponMoves->InitialSpeed = 2000.f;
	WeaponMoves->MaxSpeed = 5000.f;
	WeaponMoves->bRotationFollowsVelocity = false;
	WeaponMoves->bShouldBounce = true;
    WeaponMoves->bAutoActivate = false;
    WeaponMoves->ProjectileGravityScale = 0.01f;
	//WeaponMoves->bSimulationEnabled=false;

}


void ABase_Weapon::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, TEXT("wwwwwwwwwww"));

	UE_LOG(LogTemp, Warning, TEXT("AProjectile::OnHit--OtherComp.Name=%s"),*OtherComp->GetName());
	//后面可补&& OtherComp->IsSimulatingPhysics()
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		UE_LOG(LogTemp, Warning, TEXT("AProjectile::OnHit--OtherComp.Name=%s"),*OtherComp->GetName());
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Man->ClimbWall(GetActorLocation());
		Destroy();

		Man->isThrown = false;
		Man->NotClimbableActors.Pop();

	}
}

void ABase_Weapon::WeaponMoving(FVector const& Camera)
{
	MovingDirection = Camera;
	WeaponMoves->Velocity = Camera;
	WeaponMoves->SetActive(true,false);
	ColliBOX->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}


/*飞剑撞到可移动物体触发的逻辑*/
void ABase_Weapon::HitWall(ATestMovableActors* MovableActors)
{
	isHit = true;
	WeaponMoves->SetActive(false,false);
	Man->NowClimbingActor = MovableActors;

	//Man->ClimbWall(GetActorLocation());
	//Man->isThrown = false;
	//Man->NotClimbableActors.Pop();
	//Man->isMovingWithActor = true;
	//Destroy();
}

/*飞剑飞到一定距离还未撞墙后自动销毁*/
void ABase_Weapon::DestroyDetection()
{
	FVector TmpLoc=GetActorLocation();
	float dis = TmpLoc.Distance(TmpLoc, FlyingStart);
	if (dis > MaxDistance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, TEXT("1111111111111111"));
		Destroy();
		Man->Equipped_Weapon = NULL;
		Man->isThrown = false;
	}
}


void ABase_Weapon::MoveWithMovable()
{
	if (isHit)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, TEXT("22222222222222222"));
		
		FVector ChangedLocation = MovableDir * ((GetWorld()->GetDeltaSeconds()) * MovableActorSpeed);
		FVector TmpLocation = GetActorLocation() + ChangedLocation;
		
		SetActorLocation(TmpLocation);
	}
}

void ABase_Weapon::DestroyWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, TEXT("22222222222222222"));
	Man->NowClimbingActor = NULL;
	Man->Equipped_Weapon = NULL;
	Man->isThrown = false;
	Destroy(true);
}

void ABase_Weapon::FourDirCalculate()
{
	FVector Tmp = MovingDirection;
	UKismetMathLibrary::Vector_Normalize(Tmp);
	FVector Tmp1 = Tmp - FVector(0, 1, 0);
	FVector Tmp2 = Tmp - FVector(-1, 0, 0);
	FVector Tmp3 = Tmp - FVector(0, -1, 0);
	FVector Tmp4 = Tmp - FVector(1, 0, 0);
	float min = Tmp1.Size();
	AxesV = FVector(0, 1, 0);
	if (Tmp2.Size() < min)
	{
		min = Tmp2.Size();
		AxesV = FVector(-1, 0, 0);
	}
	if (Tmp3.Size() < min)
	{
		min = Tmp3.Size();
		AxesV = FVector(0, -1, 0);
	}
	if (Tmp4.Size() < min)
	{
		min = Tmp4.Size();
		AxesV = FVector(1, 0, 0);
	}
}

// Called when the game starts or when spawned
void ABase_Weapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABase_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isFlying)
	{
		DestroyDetection();

	}
	if (isHit)
	{
		MoveWithMovable();
	}	
	//SetActorLocation(TempPosition);

}

