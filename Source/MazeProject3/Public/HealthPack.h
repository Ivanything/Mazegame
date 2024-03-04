// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Kismet/GameplayStatics.h"
#include "HealthPack.generated.h"

/**
 * 
 */
UCLASS()
class MAZEPROJECT3_API AHealthPack : public APickup
{
	GENERATED_BODY()

public:
	virtual void Collect(APlayerCharacter* p);

	UPROPERTY(EditAnywhere)
		float healthAmount = 5;

	UPROPERTY(EditAnywhere)
		USoundBase* sound;
	
};
