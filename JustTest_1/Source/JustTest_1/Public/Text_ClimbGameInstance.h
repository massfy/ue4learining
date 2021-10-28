// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Text_ClimbGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JUSTTEST_1_API UText_ClimbGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	TArray<FName>GameLevels = { "one","two","three" };
	
};
