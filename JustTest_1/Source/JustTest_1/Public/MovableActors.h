// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovableActors.generated.h"

UCLASS()
class JUSTTEST_1_API AMovableActors : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovableActors();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovableActor")
	//	class USphereComponent* RTComp;

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

	FVector UPP = FVector(0, 0, 90);
	FVector RIGHT = FVector(0, 90, 0);
	FVector FORWORD = FVector(90, 0, 0);
	FVector Direction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	//UFUNCTION()
	//	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	//		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);		//�ֿ�ʱ���ú���

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
