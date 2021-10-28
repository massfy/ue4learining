// Fill out your copyright notice in the Description page of Project Settings.


#include "Base_Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Base_Weapon.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Animation/AnimInstance.h"

#include "MovableActors.h"
#include "TestMovableActors.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ABase_Character::ABase_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//��������ɱ�
	CameraArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArmComp"));
	CameraArmComp->SetupAttachment(RootComponent);
	CameraArmComp->TargetArmLength = 600;
	CameraArmComp->bUsePawnControlRotation = true;

	//�����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArmComp, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;


	Weapon_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon1"));
	Weapon_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon2"));
	Weapon_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon3"));

	SpringArmComp1 = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent1"));
	SpringArmComp2 = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent2"));
	SpringArmComp3 = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent3"));

	SpringArmComp1->SetupAttachment(RootComponent);
	SpringArmComp2->SetupAttachment(RootComponent);
	SpringArmComp3->SetupAttachment(RootComponent);

	Weapon_1->SetupAttachment(SpringArmComp1);
	Weapon_2->SetupAttachment(SpringArmComp2);
	Weapon_3->SetupAttachment(SpringArmComp3);

	Ro_Mid = FRotator(0, 180, 0);
	Ro_Weapon1 = FRotator(0, 135, 0);
	Ro_Weapon2 = FRotator(0, 180, 0);
	Ro_Weapon3 = FRotator(0, 225, 0);

	SpringArmComp1->SetRelativeRotation(Ro_Weapon1);
	SpringArmComp2->SetRelativeRotation(Ro_Weapon2);
	SpringArmComp3->SetRelativeRotation(Ro_Weapon3);

	isThrown = false;

	NotClimbableActors.Add(this);
	
}

/*�л�����ʱ������������ת*/
void ABase_Character::SetRo(FRotator tmp)
{
	Ro_Weapon1 = Ro_Weapon1 + tmp;
	Ro_Weapon2 = Ro_Weapon2 + tmp;
	Ro_Weapon3 = Ro_Weapon3 + tmp;

	SpringArmComp1->SetRelativeRotation(Ro_Weapon1);
	SpringArmComp2->SetRelativeRotation(Ro_Weapon2);
	SpringArmComp3->SetRelativeRotation(Ro_Weapon3);
}

/*����������л�����ʱ�ĺ���*/
void ABase_Character::SetWeaponRotation2()
{
	if(!isThrown)
	{
		SetWeapon(EWeapon::EW_Weapon2);
		TempWeapon = Weapon_2;
		FRotator tmp = Ro_Mid - Ro_Weapon2;
		SetRo(tmp);
		WeaponAppear();
		Equipped_Weapon->CurrentWeaponNum = EWeaponW::EW_Weapon2;
	}
}

void ABase_Character::SetWeaponRotation3()
{
	if (!isThrown) 
	{
		SetWeapon(EWeapon::EW_Weapon3);
		TempWeapon = Weapon_3;
		FRotator tmp = Ro_Mid - Ro_Weapon3;
		SetRo(tmp);
		WeaponAppear();
		Equipped_Weapon->CurrentWeaponNum = EWeaponW::EW_Weapon3;
	}
}

void ABase_Character::SetWeaponRotation1()
{
	if(!isThrown)
	{
		SetWeapon(EWeapon::EW_Weapon1);
		TempWeapon = Weapon_1;
		FRotator tmp = Ro_Mid - Ro_Weapon1;
		SetRo(tmp);
		WeaponAppear();
		Equipped_Weapon->CurrentWeaponNum = EWeaponW::EW_Weapon1;
	}
}

/*��������������*/
void ABase_Character::WeaponSpawn_Implementation(UClass* PawnClass)
{
	if (Equipped_Weapon)
		Equipped_Weapon->Destroy();
	FVector Location = TempWeapon->GetComponentLocation();
	UWorld* MyWorld = GetWorld();
	if (MyWorld)
	{
		ABase_Weapon* MyWeapon = MyWorld->SpawnActor<ABase_Weapon>(PawnClass, Location, FRotator(0.f));
		Equipped_Weapon = MyWeapon;
		Equipped_Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponSocket");
		Equipped_Weapon->Man = this;
		NotClimbableActors.Add(Equipped_Weapon);
	}
}

/*���õ�ǰ����������ֽ�*/
void ABase_Character::SetWeapon(EWeapon WeaponNum)
{
	CurrentWeaponNum = WeaponNum;
}

/*�ɽ�*/
void ABase_Character::ThrowWeapon()
{
	if (Equipped_Weapon&&!isThrown)
	{
		FVector HitRes=TargetDetection();

		FVector TempPos = Equipped_Weapon->GetActorLocation();
		FRotator TempRot = Equipped_Weapon->GetActorRotation();
		Equipped_Weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		isThrown = true;

		//FRotator StartRotator=UKismetMathLibrary::MakeRotationFromAxes();

		Equipped_Weapon->SetActorLocation(TempPos);
		Equipped_Weapon->SetActorRotation(FlyDirection);

		//�˴�����weapon���õ�move����
		Equipped_Weapon->FlyingStart = TempPos;
		Equipped_Weapon->WeaponMoving(HitRes-TempPos);	
		Equipped_Weapon->isFlying = true;
	}
		
}

void ABase_Character::ArriveWeaponPos()
{
	if(NowClimbingActor&&Equipped_Weapon)
	{
		ClimbWall(Equipped_Weapon->GetActorLocation());
		NowClimbingActor->HittedWeapon = NULL;

		isThrown = false;
		NotClimbableActors.Pop();
		isMovingWithActor = true;
		
		Equipped_Weapon->Destroy();
		Equipped_Weapon = NULL;
	}
}

/*�ɽ�������*/
FVector ABase_Character::TargetDetection()
{
	FVector HitRes;
	if (Equipped_Weapon)
	{
		float MaxDistance = MaxWeaponMoving;

		FVector CamLoc;
		FRotator CamRot;
		Controller->GetPlayerViewPoint(CamLoc, CamRot);
		const FVector Direction = CamRot.Vector();
		const FVector TraceStart=Equipped_Weapon->GetActorLocation();
		const FVector TraceEnd = TraceStart + (Direction * MaxDistance);

		FHitResult Hit;
		const bool bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), TraceStart, TraceEnd, ETraceTypeQuery::TraceTypeQuery1, false, NotClimbableActors, EDrawDebugTrace::ForOneFrame, Hit, true, FLinearColor::Green, FLinearColor::Red, 5.0f);
		if (bHit)
		{
			HitRes = Hit.ImpactPoint;
			DrawDebugLine(GetWorld(), TraceStart, Hit.Location, FColor::Green, false, 1.0f);
		}
		else
		{
			HitRes = TraceEnd;
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f);
		}

		/*���������Ƿɽ���ʼ��rotator*/
		FVector StartDirection = HitRes - TraceStart;
		FRotator TempRo =UKismetMathLibrary::Conv_VectorToRotator(StartDirection);
		//���ɽ�z������
		FlyDirection = TempRo - FRotator(90, 0, 0);

		
	}
	return HitRes;
}

/*Debug Function*/
void ABase_Character::CommonTraceDetection()
{
	float distance = 100;

	/*���������ʼ��*/
	FVector TraceStart = GetActorLocation();
	//GetActorForwardVector().Normalize(0.0001);
	FVector TraceEnd = TraceStart + (this->GetActorForwardVector())*distance;
	DrawDebugLine(GetWorld(), GetActorLocation(),GetActorLocation()+ GetActorForwardVector()*1000, FColor::Red, false, 1.0f);
}

/*�ɽ�������ײ�����*/
void ABase_Character::ClimbWall(const FVector &HitPoint)
{
	SetActorLocation(HitPoint);
	ObstacleDetection_Init();
	StateChanging(EStateChange::WalkToClimb);
}

/*��������������ɫ��ǽ�ϵ��ж�����*/
void ABase_Character::SetClimbingDirection()
{
	FRotator TempRo =UKismetMathLibrary::Conv_VectorToRotator(FVector(ClimbUpValue, ClimbRightValue, 0.0));
	ClimbingDirection = TempRo.Yaw;
	//ÿ�α������㣬���������쳣
	ClimbUpValue = 0;
	ClimbRightValue = 0;
}

/*��ʼ��������߼���*/
void ABase_Character::ObstacleDetection_Init()
{
	float distance = 100;

	/*���������ʼ��*/
	FVector TraceStart = GetActorLocation();
	//GetActorForwardVector().Normalize(0.0001);
	FVector TraceEnd = TraceStart + (this->GetActorForwardVector())*distance;

	/* FHitResults������ܽ�� */
	FHitResult Hit;
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), TraceStart, TraceEnd, ETraceTypeQuery::TraceTypeQuery1, false, NotClimbableActors, EDrawDebugTrace::ForOneFrame, Hit, true, FLinearColor::Green, FLinearColor::Red, 5.0f);
	
	ObstacleLocation = Hit.Location;
	ObstacleNormalDir = Hit.Normal;

	/*��������յ�*/
	FVector ObstacleEnd = ObstacleEndCalculation();
	FHitResult Hit2;
	const bool bHit2 = UKismetSystemLibrary::LineTraceSingle(GetWorld(), TraceStart, ObstacleEnd, ETraceTypeQuery::TraceTypeQuery1, false, NotClimbableActors, EDrawDebugTrace::ForOneFrame, Hit2, true, FLinearColor::Green, FLinearColor::Red, 5.0f);
	
	ObstacleEndLocation = Hit2.Location;
}

/*����ʱ������߼���*/
void ABase_Character::ObstacleDetection_Climbing()
{
	float distance = 100;

	/*���������ʼ��*/
	FVector TraceStart = GetActorLocation();
	//GetActorForwardVector().Normalize(0.0001);
	FVector TraceEnd = TraceStart + (this->GetActorForwardVector())*distance;

	DrawDebugLine(GetWorld(), GetActorLocation(),GetActorLocation()+ GetActorForwardVector()*1000, FColor::Red, false, 1.0f);

	/* FHitResults������ܽ�� */
	FHitResult Hit;
	//const bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility,TraceParams);
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), TraceStart, TraceEnd, ETraceTypeQuery::TraceTypeQuery1, false, NotClimbableActors, EDrawDebugTrace::ForOneFrame, Hit, true, FLinearColor::Green, FLinearColor::Red, 5.0f);

	ObstacleLocation = Hit.Location;

	ObstacleNormalDir=UKismetMathLibrary::VInterpTo_Constant(ObstacleNormalDir, Hit.Normal, GetWorld()->GetDeltaSeconds(), 10.0);

	/*��������յ�*/
	FVector ObstacleEnd = ObstacleEndCalculation();
	FHitResult Hit2;
	const bool bHit2 = UKismetSystemLibrary::LineTraceSingle(GetWorld(), TraceStart, ObstacleEnd, ETraceTypeQuery::TraceTypeQuery1, false, NotClimbableActors, EDrawDebugTrace::ForOneFrame, Hit2, true, FLinearColor::Green, FLinearColor::Red, 5.0f);
	ObstacleEndLocation = Hit2.Location;
	if (!bHit2)
	{
		/*��������û����ײ֤���������嶥�ˣ����õ�½��⺯��*/
		/*�ڴ������ж��Ƿ�ɵ�¼�ķ�֧*/
		CheckEnoughSpaceForLanding();

		/*����Ӧ�õȶ������������ٵ���*/

		//if (isEndClimbUp)
		//{
			StateChanging(EStateChange::ClimbToWalk);
		
			//�����Ƿ��ڸ��������ƶ�
			if (isMovingWithActor)
			{
				isMovingWithActor = false;
			}
			isEndClimbUp = false;
		//}
	}
}

/*�ڶ���������ߵ�λ������*/
FVector ABase_Character::ObstacleEndCalculation()
{
	float Distance2D = 150;

	FVector tempV = ObstacleLocation - GetActorLocation();
	UKismetMathLibrary::Vector_Normalize(tempV);
	tempV = tempV + FVector(0, 0, 1);

	FVector ObstacleEnd = GetActorLocation() + tempV * Distance2D;
	return ObstacleEnd;
}

/*������ײ���߼����ɫ��ǰ��*/
void ABase_Character::FindClimbingRotation()
{
	FVector VOnWall = ObstacleEndLocation - ObstacleLocation;
	UKismetMathLibrary::Vector_Normalize(VOnWall);

	//��ɫ��ǽ�����ҷ���
	FVector RightVOnWall;
	RightVOnWall=RightVOnWall.CrossProduct(VOnWall, ObstacleNormalDir);
	RightVOnWall = RightVOnWall * invert;

	//up����
	FVector CLV;
	CLV=CLV.CrossProduct(RightVOnWall, ObstacleNormalDir);

	//forward����
	FVector CLF = ObstacleNormalDir * invert;

	ClimbingRotation = UKismetMathLibrary::MakeRotationFromAxes(CLF,RightVOnWall,CLV);

	UKismetMathLibrary::Vector_Normalize(CLV);
	ClimbingUpV = CLV;
	
	UKismetMathLibrary::Vector_Normalize(RightVOnWall);
	ClimbingRightV = RightVOnWall;
	
}

/*ÿ֡���õ���������*/
void ABase_Character::ClimbingTick()
{
	if (isClimbing)
	{
		
		//FRotator RO_Character(0,0,0);
		FindClimbingRotation();
		SetActorRotation(ClimbingRotation);
		FVector ForceDir = ObstacleNormalDir * invert;
		ForceDir.Normalize(0.0001);
		GetCharacterMovement()->AddForce(ForceDir * Force);
		ObstacleDetection_Climbing();
		if (isMovingWithActor&&NowClimbingActor)
		{
			GetMovableActorDir();
			MoveWithMovableActor(MovableActorDir);
		}
	}
	else
	{

	}
}

/*״̬�л�ʱ����*/
void ABase_Character::StateChanging(const EStateChange& ESC)
{
	switch (ESC)
	{
		case EStateChange::ClimbToClimb:
		{
			//GetCharacterMovement()->SetbOrientRotationToMovement
			break;
		}
		case EStateChange::ClimbToWalk:
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			GetCharacterMovement()->bOrientRotationToMovement = true;
			isClimbing = false;
			isMovingWithActor = false;
			if (NowClimbingActor)
			{
				NowClimbingActor = NULL;
			}
			break;
		}
		case EStateChange::WalkToClimb:
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
			GetCharacterMovement()->bOrientRotationToMovement = false;

			isClimbing = true;

			break;
		}
	}
}

/*��ɫ��ǽ����Ծ�ƶ�ʱ���ú���*/
void ABase_Character::ClimbingDash()
{
	UAnimInstance* Instance = GetMesh()->GetAnimInstance();
	if (Instance)
	{
		if (ClimbingDirection >= 80 && ClimbingDirection <= 100)
		{
			if (DashWhileClimbing1)
			{
				Instance->Montage_Play(DashWhileClimbing1);
			}
		}
		else if (ClimbingDirection >= 35 && ClimbingDirection <= 55)
		{
			if (DashWhileClimbing2)
			{
				Instance->Montage_Play(DashWhileClimbing2);
			}
		}
		else if (ClimbingDirection >= -5 && ClimbingDirection <= 5)
		{
			if (DashWhileClimbing3)
			{
				Instance->Montage_Play(DashWhileClimbing3);
			}
		}
		else if (ClimbingDirection >= -55 && ClimbingDirection <= -35)
		{
			if (DashWhileClimbing4)
			{
				Instance->Montage_Play(DashWhileClimbing4);
			}
		}
		else if (ClimbingDirection >= -100 && ClimbingDirection <= -80)
		{
			if (DashWhileClimbing5)
			{
				Instance->Montage_Play(DashWhileClimbing5);
			}
		}
		else
		{
			StateChanging(EStateChange::ClimbToWalk);
		}
	}

}

void ABase_Character::GetMovableActorDir()
{
	MovableActorDir = NowClimbingActor->Direction;
	UKismetMathLibrary::Vector_Normalize(MovableActorDir);
	MovableActorSpeed = NowClimbingActor->Speed;

	//����ֹͣ�ƶ����ɫҲҪͣ
	if (!NowClimbingActor->isMoving)
	{
		isMovingWithActor = false;
	}
}

//�������ƶ���c++�汾
//void ABase_Character::MoveWithMovableActor(FVector Dir)
//{
//	if (isClimbing && NowClimbingActor->isMoving)
//	{
//		
//		Dir.Normalize(0.0001);
//
//		FVector ChangedLocation = Dir * ((GetWorld()->GetDeltaSeconds()) * MovableActorSpeed);
//		FVector TmpLocation = GetActorLocation() + ChangedLocation;
//
//		GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, TEXT("22222222222222222"));
//
//		SetActorLocation(TmpLocation);
//	}
//
//}

/*��ɫ����ǽ�Ķ�����ж��Ƿ���λ�õ�½*/
void ABase_Character::CheckEnoughSpaceForLanding()
{
	float CharacterThickness = 50.0f;
	FVector CharacterHeight(0, 0, 200);

	/*��������ײ���*/
	FVector TraceStart = GetActorLocation() + CharacterHeight;
	FVector TraceEnd = TraceStart + (UKismetMathLibrary::GetForwardVector(GetActorRotation())) * CharacterThickness;

	FHitResult Hit;
	const bool bHit = UKismetSystemLibrary::CapsuleTraceSingle(GetWorld(), TraceStart, TraceEnd, 50.0, 50.0,ETraceTypeQuery::TraceTypeQuery1 , false,NotClimbableActors, EDrawDebugTrace::ForDuration, Hit, true,FLinearColor::Red,FLinearColor::Green,5.0f);

	/*������ײ������λ���Ƿ����*/
	FVector CheckPosStart = Hit.TraceEnd;
	FVector CheckPosEnd = CheckPosStart - FVector(0, 0, 250.0);

	FHitResult Hit2;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), CheckPosStart, CheckPosEnd, ETraceTypeQuery::TraceTypeQuery1, false, NotClimbableActors, EDrawDebugTrace::ForOneFrame, Hit2, true, FLinearColor::Green, FLinearColor::Red, 5.0f);

	if (Hit2.bBlockingHit)
	{
		FLatentActionInfo ActionInfo;
		ActionInfo.CallbackTarget=this;
		FVector TargetPos = Hit2.ImpactPoint + FVector(0, 0, 100);
		UKismetSystemLibrary::MoveComponentTo(RootComponent, TargetPos, GetActorRotation(), true, true, 0.8, true,EMoveComponentAction::Move, ActionInfo);
	
		UAnimInstance* Instance = GetMesh()->GetAnimInstance();
		if (ClimbToWalkAnimMontage && Instance)
		{
			Instance->Montage_Play(ClimbToWalkAnimMontage);
		}
	}
}

void ABase_Character::EndClimbing()
{

	StateChanging(EStateChange::ClimbToWalk);
}

void ABase_Character::EndClimbingUp(bool isEndClimbup)
{
	isEndClimbUp = isEndClimbup;
}

void ABase_Character::MoveForward(float value)
{
	if (Controller && value != 0)
	{
		if (!isClimbing)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0.f, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);		//������ת����
			AddMovementInput(Direction, value);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, TEXT("xxxx"));
			/*?*/
			AddMovementInput(ClimbingUpV, value);
			ClimbUpValue = value;
			DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation()+ClimbingUpV*ClimbUpValue*1000, FColor::Blue, false, 1.0f);
		}
	}
}

void ABase_Character::MoveRight(float value)
{
	if (Controller && value != 0 )
	{
		if (!isClimbing)
		{
			const FRotator Rotation = Controller->GetControlRotation();		//�õ���������ת
			const FRotator YawRotation(0.f, Rotation.Yaw, 0);				//��������ת��Ϊ������ת��ֵ

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);		//������ת����
			AddMovementInput(Direction, value);

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 9, FColor::Cyan, TEXT("xxxx"));
			AddMovementInput(ClimbingRightV, value);
			ClimbRightValue = value;
		}
		
	}
}

void ABase_Character::MyJump()
{
	if (!isClimbing)
	{
		Jump();
	}
	else
	{
		ClimbingDash();
	}
}

void ABase_Character::CharacterDead()
{
	isDead = true;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);
	DisableInput(PlayerController);

	//����ʱ������������
	UAnimInstance* Instance = GetMesh()->GetAnimInstance();
	if (ClimbToWalkAnimMontage && Instance)
	{
		Instance->Montage_Play(ClimbToWalkAnimMontage);
		Instance->Montage_JumpToSection(FName("Death"), ClimbToWalkAnimMontage);

	}
	//����������ر���ײ(�����ô�)
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABase_Character::DeathEnd()
{

}

// Called when the game starts or when spawned
void ABase_Character::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ABase_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ClimbingTick();
	SetClimbingDirection();
}

// Called to bind functionality to input
void ABase_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ChangeWeapon1", IE_Pressed, this, &ABase_Character::SetWeaponRotation1);
	PlayerInputComponent->BindAction("ChangeWeapon2", IE_Pressed, this, &ABase_Character::SetWeaponRotation2);
	PlayerInputComponent->BindAction("ChangeWeapon3", IE_Pressed, this, &ABase_Character::SetWeaponRotation3);

	//PlayerInputComponent->BindAction("ChangeWeapon", IE_Released, this, &ABase_Character::DestroyWeapon);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this,&ABase_Character::MyJump);
	PlayerInputComponent->BindAction("Jump", IE_Released,this, &ABase_Character::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward",this, &ABase_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this, &ABase_Character::MoveRight);

	PlayerInputComponent->BindAxis("CameraPitch", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("CameraYaw", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("ThrowWeapon", IE_Pressed, this, &ABase_Character::ThrowWeapon);
	PlayerInputComponent->BindAction("ArriveWeaponPos", IE_Pressed, this, &ABase_Character::ArriveWeaponPos);
}
