// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Weapon.generated.h"

class ABase_Character;

UENUM(BlueprintType)
enum class EWeaponW :uint8	//ö������
{
	EW_Weapon1,
	EW_Weapon2,
	EW_Weapon3
};

UCLASS()
class JUSTTEST_1_API ABase_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_Weapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* MeshComp;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	//UStaticMeshComponent* WeaponOri;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	class UBoxComponent* ColliBOX;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	//class UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Weapon")
	class UProjectileMovementComponent* WeaponMoves;


	void WeaponMoving(FVector const& Camera);

	ABase_Character* Man;
	//�ɽ�����
	FVector MovingDirection;

	EWeaponW CurrentWeaponNum;

	/*��ǽʵ��֮ǰonhit�Ĺ���*/
	void HitWall(class ATestMovableActors* MovableActors);
	/*����һ�ξ�����������*/
	void DestroyDetection();
	bool isFlying=false;
	FVector FlyingStart;

	//��Զ�ɷ��о���
	float MaxDistance = 3000.f;

	//�Ƿ��������
	bool isHit=false;

	//����������һ���ƶ�
	FVector MovableDir;
	float MovableActorSpeed;
	void MoveWithMovable();

	//����ֹͣ�ƶ�����������
	void DestroyWeapon();

	//���ݷɽ��������������ڳ��ĸ������ƶ�
	void FourDirCalculate();
	FVector AxesV;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
