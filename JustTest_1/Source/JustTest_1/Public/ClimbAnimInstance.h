// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ClimbAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class JUSTTEST_1_API UClimbAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		class ABase_Character* Man;


#if 1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float ClimbingDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool isClimbing=false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool isInAir=false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	class APawn* Pawn;				//主角类指针

	virtual void NativeInitializeAnimation()override;		//初始化动作

	UFUNCTION(BlueprintCallable, Category = "AnimationProperty")
	void UpdateAnimationProperties();			//更新一些动画属性

	/*此处是可移动物体的速度*/
	float MovableSpeed = 250.f;

#endif
	
};
