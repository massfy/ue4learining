// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Base_Character.generated.h"

//class ABase_Weapon;

UENUM(BlueprintType)
enum class EWeapon :uint8	//枚举类型
{
	EW_Weapon1,
	EW_Weapon2,
	EW_Weapon3
};

UENUM(BlueprintType)
enum class EStateChange :uint8
{
	WalkToClimb,
	ClimbToWalk,
	ClimbToClimb,
};

UENUM(BlueprintType)
enum class ECommonState :uint8
{
	Walking,
	Climbing,
};

UCLASS()
class JUSTTEST_1_API ABase_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABase_Character();

//basecomp
#if 1
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* CameraArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* Camera;
#endif

//WeaponComp
#if 1
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		class USpringArmComponent* SpringArmComp1;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Weapon")
	class UStaticMeshComponent* Weapon_1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	USpringArmComponent* SpringArmComp2;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Weapon")
	UStaticMeshComponent* Weapon_2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	USpringArmComponent* SpringArmComp3;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Weapon")
	UStaticMeshComponent* Weapon_3;

	UStaticMeshComponent* TempWeapon;

	UPROPERTY(VisibleAnywhere)
	class ABase_Weapon* Equipped_Weapon;

#endif

//WeaponAction
#if 1
	UFUNCTION(BlueprintImplementableEvent)
		void WeaponAppear();

	UFUNCTION(BlueprintImplementableEvent)
		void WeaponSpawnInHand();

	UPROPERTY(BlueprintReadWrite)
	bool WeaponOnScreen;


	void SetRo(FRotator tmp);

	void SetWeaponRotation1();
	void SetWeaponRotation2();
	void SetWeaponRotation3();

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)	
	//void EquipWeapon(UClass* PawnClass);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void WeaponSpawn(UClass* PawnClass);

#endif

//WeaponData
#if 1
	FRotator Ro_Weapon1;
	FRotator Ro_Weapon2;
	FRotator Ro_Weapon3;
	FRotator Ro_Mid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABase_Weapon>WeaponToEquip;		
	//武器种类，可以在蓝图内动态改变变量

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EWeapon CurrentWeaponNum;	//当前武器

	void SetWeapon(EWeapon WeaponNum);

	bool isThrown=false;

#endif

//角色扔剑挂墙
#if 1
	FRotator FlyDirection;
	/*武器最远可飞行距离*/
	const float MaxWeaponMoving = 3000.f;

	//扔剑
	UFUNCTION()
	void ThrowWeapon();

	//瞬移到扔剑位置
	UFUNCTION()
	void ArriveWeaponPos();

	//根据角色视野方向获得飞剑方向
	UFUNCTION()
		FVector TargetDetection();


	//DebugFunction
	UFUNCTION()
		void CommonTraceDetection();

	//角色挂墙
	void ClimbWall(const FVector &HitPoint);

#endif

//角色攀爬
#if 1
	//不可攀爬物体
	TArray<AActor*>NotClimbableActors;

	bool isClimbing=false;
	float ClimbingDirection;
	float ClimbUpValue;
	float ClimbRightValue;
	void SetClimbingDirection();

	float Force = 1000000;
	float invert = -1;

	//初始化向量检测
	void ObstacleDetection_Init();
	//攀爬时向量检测
	void ObstacleDetection_Climbing();
	FVector ObstacleEndCalculation();
	
	FVector ObstacleNormalDir;
	FVector ObstacleLocation;
	FVector ObstacleEndLocation;

	FVector ClimbingRightV;
	FVector ClimbingUpV;

	FRotator ClimbingRotation;

	//设定角色攀爬时的方向
	void FindClimbingRotation();
	//每帧的执行函数
	void ClimbingTick();
	//状态改变时执行函数
	void StateChanging(const EStateChange&ESC);
	
	//角色墙上跳跃
	void ClimbingDash();
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="DashWhileClimbing")
		class UAnimMontage* DashWhileClimbing1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="DashWhileClimbing")
		class UAnimMontage* DashWhileClimbing2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="DashWhileClimbing")
		class UAnimMontage* DashWhileClimbing3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="DashWhileClimbing")
		class UAnimMontage* DashWhileClimbing4;
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="DashWhileClimbing")
		class UAnimMontage* DashWhileClimbing5;


#endif

/*角色在移动物体上的状态*/
#if 1
	//角色所爬物体
	class ATestMovableActors* NowClimbingActor;

	//角色是否跟随物体移动
	bool isMovingWithActor=false;

	//角色所爬物体移动方向
	FVector MovableActorDir;

	void GetMovableActorDir();

	//角色所爬物体的移动速度
	float MovableActorSpeed;

	//角色跟随物体自动移动
	UFUNCTION(BlueprintImplementableEvent)
	void MoveWithMovableActor(FVector Dir);


#endif

/*角色登陆*/
#if 1
	void CheckEnoughSpaceForLanding();

	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UAnimMontage* ClimbToWalkAnimMontage;

	void EndClimbing();

	UFUNCTION(BlueprintCallable)
	void EndClimbingUp(bool isEndClimbup);
	bool isEndClimbUp=false;


#endif

/*角色基础操作*/
#if 1
	void MoveForward(float value);

	void MoveRight(float value);

	void MyJump();

	//void MyStopJumping(float value);


#endif

/*角色状态*/
#if 1
	bool isDead=false;

	//角色摔死
	void CharacterDead();

	UFUNCTION(BlueprintCallable)
	void DeathEnd();

#endif


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
