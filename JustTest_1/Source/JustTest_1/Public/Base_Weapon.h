// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Base_Weapon.generated.h"

class ABase_Character;

UENUM(BlueprintType)
enum class EWeaponW :uint8	//枚举类型
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
	//飞剑方向
	FVector MovingDirection;

	EWeaponW CurrentWeaponNum;

	/*用墙实现之前onhit的功能*/
	void HitWall(class ATestMovableActors* MovableActors);
	/*飞行一段距离后必须销毁*/
	void DestroyDetection();
	bool isFlying=false;
	FVector FlyingStart;

	//最远可飞行距离
	float MaxDistance = 3000.f;

	//是否击中箱子
	bool isHit=false;

	//武器与箱子一起移动
	FVector MovableDir;
	float MovableActorSpeed;
	void MoveWithMovable();

	//箱子停止移动后武器销毁
	void DestroyWeapon();

	//根据飞剑方向计算其大体在朝哪个方向移动
	void FourDirCalculate();
	FVector AxesV;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
