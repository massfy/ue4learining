// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PawnVolume.generated.h"

class ABase_Actor;

UCLASS()
class JUSTTEST_1_API APawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent *SpawnBox;

	UFUNCTION(BlueprintPure)
		FVector GetSpawnPoint();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void ActorSpawn(UClass *MyActor,FVector const&Location);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="MyActor")
	TSubclassOf<ABase_Actor>PawnActor;

	//UFUNCTION(Bluepr)

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
