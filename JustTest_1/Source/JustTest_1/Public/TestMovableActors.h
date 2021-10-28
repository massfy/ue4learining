// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestMovableActors.generated.h"

UCLASS()
class JUSTTEST_1_API ATestMovableActors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestMovableActors();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovableActor")
		class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "MovableActor")
		class UBoxComponent* BoxComp;

	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
			bool bFromSweep, const FHitResult& SweepResult);	//��ײʱ���õĺ���

	
	void MeshMove(FVector Dir);

	float Speed = 250.f;
	bool isMoving = false;
	FVector UPP = FVector(0, 0, 1);
	FVector RIGHT = FVector(0, 1, 0);
	FVector FORWORD = FVector(1, 0, 0);
	FVector Direction;

	/*�����ƶ�һ�ξ����ֹͣ*/
	FVector StartLoc;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MovableActors")
	float MaxDistance=3000.f;

	void StopDetection();

	class ABase_Weapon* HittedWeapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
