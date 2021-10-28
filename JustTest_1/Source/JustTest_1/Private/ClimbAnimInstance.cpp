// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbAnimInstance.h"
#include "Base_Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UClimbAnimInstance::NativeInitializeAnimation()
{
	if (!Pawn)
		Pawn = TryGetPawnOwner();

	Man = Cast<ABase_Character>(Pawn);
}

void UClimbAnimInstance::UpdateAnimationProperties()
{
	if (!Pawn)
		Pawn = TryGetPawnOwner();		//拿到主角

	if (Pawn)
	{
		isInAir = Pawn->GetMovementComponent()->IsFalling();
		ClimbingDirection = Man->ClimbingDirection;
		isClimbing = Man->isClimbing;


		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed;

		/*此处判断角色运动方向相对箱子运动的相对运动方向，以此来确定相对运动速度*/
		if (isClimbing&&Man->isMovingWithActor)
		{
			FVector CharacterV = Man->GetActorForwardVector();
			UKismetMathLibrary::Vector_Normalize(CharacterV);
			FVector TmpV = CharacterV - Man->MovableActorDir;

			if (Man->CurrentWeaponNum == EWeapon::EW_Weapon1)
			{
				LateralSpeed = FVector(Speed.X, Speed.Y, Speed.Z);		
			}
			else if (Man->CurrentWeaponNum == EWeapon::EW_Weapon2)
			{
				if (TmpV.IsNearlyZero(0.1))
				{
					LateralSpeed = FVector(Speed.X,Speed.Y-MovableSpeed ,Speed.Z);	
				}
				else
				{
					LateralSpeed = FVector(Speed.X, Speed.Y, Speed.Z);
				}
			}
			else
			{
				if (TmpV.IsNearlyZero(0.1))
				{
					LateralSpeed = FVector(Speed.X-MovableSpeed, Speed.Y,Speed.Z);
				}
				else
				{
					LateralSpeed = FVector(Speed.X, Speed.Y,Speed.Z);
				}
				
			}
		}
		else
		{
			LateralSpeed = FVector(Speed.X, Speed.Y, Speed.Z);
		}
		
		MovementSpeed = LateralSpeed.Size();	
	}
}
