// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Actor.generated.h"

UCLASS()
class JUSTTEST_1_API ABase_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_Actor();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Mesh")
		class UStaticMeshComponent* MeshComp;

//	virtual ABase_Actor* Clone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
