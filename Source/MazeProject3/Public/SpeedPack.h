// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "SpeedPack.generated.h"

/**
 * 
 */
UCLASS()
class MAZEPROJECT3_API ASpeedPack : public APickup
{
	GENERATED_BODY()

public:
	virtual void Collect(APlayerCharacter* p);

	UPROPERTY(EditAnywhere)
		float speedTimer = 3;
	
};
