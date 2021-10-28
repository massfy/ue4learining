// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Base_Character.generated.h"

//class ABase_Weapon;

UENUM(BlueprintType)
enum class EWeapon :uint8	//ö������
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
	//�������࣬��������ͼ�ڶ�̬�ı����

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EWeapon CurrentWeaponNum;	//��ǰ����

	void SetWeapon(EWeapon WeaponNum);

	bool isThrown=false;

#endif

//��ɫ�ӽ���ǽ
#if 1
	FRotator FlyDirection;
	/*������Զ�ɷ��о���*/
	const float MaxWeaponMoving = 3000.f;

	//�ӽ�
	UFUNCTION()
	void ThrowWeapon();

	//˲�Ƶ��ӽ�λ��
	UFUNCTION()
	void ArriveWeaponPos();

	//���ݽ�ɫ��Ұ�����÷ɽ�����
	UFUNCTION()
		FVector TargetDetection();


	//DebugFunction
	UFUNCTION()
		void CommonTraceDetection();

	//��ɫ��ǽ
	void ClimbWall(const FVector &HitPoint);

#endif

//��ɫ����
#if 1
	//������������
	TArray<AActor*>NotClimbableActors;

	bool isClimbing=false;
	float ClimbingDirection;
	float ClimbUpValue;
	float ClimbRightValue;
	void SetClimbingDirection();

	float Force = 1000000;
	float invert = -1;

	//��ʼ���������
	void ObstacleDetection_Init();
	//����ʱ�������
	void ObstacleDetection_Climbing();
	FVector ObstacleEndCalculation();
	
	FVector ObstacleNormalDir;
	FVector ObstacleLocation;
	FVector ObstacleEndLocation;

	FVector ClimbingRightV;
	FVector ClimbingUpV;

	FRotator ClimbingRotation;

	//�趨��ɫ����ʱ�ķ���
	void FindClimbingRotation();
	//ÿ֡��ִ�к���
	void ClimbingTick();
	//״̬�ı�ʱִ�к���
	void StateChanging(const EStateChange&ESC);
	
	//��ɫǽ����Ծ
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

/*��ɫ���ƶ������ϵ�״̬*/
#if 1
	//��ɫ��������
	class ATestMovableActors* NowClimbingActor;

	//��ɫ�Ƿ���������ƶ�
	bool isMovingWithActor=false;

	//��ɫ���������ƶ�����
	FVector MovableActorDir;

	void GetMovableActorDir();

	//��ɫ����������ƶ��ٶ�
	float MovableActorSpeed;

	//��ɫ���������Զ��ƶ�
	UFUNCTION(BlueprintImplementableEvent)
	void MoveWithMovableActor(FVector Dir);


#endif

/*��ɫ��½*/
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

/*��ɫ��������*/
#if 1
	void MoveForward(float value);

	void MoveRight(float value);

	void MyJump();

	//void MyStopJumping(float value);


#endif

/*��ɫ״̬*/
#if 1
	bool isDead=false;

	//��ɫˤ��
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
