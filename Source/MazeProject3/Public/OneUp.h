// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "OneUp.generated.h"

/**
 * 
 */
UCLASS()
class MAZEPROJECT3_API AOneUp : public APickup
{
	GENERATED_BODY()

public:
	virtual void Collect(APlayerCharacter* p);

	UPROPERTY(EditAnywhere)
		USoundBase* sound;

	UFUNCTION(BlueprintImplementableEvent, Category = "Output")
		void GiveExtraLife();
};
