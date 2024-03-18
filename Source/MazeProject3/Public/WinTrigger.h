// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "WinTrigger.generated.h"

/**
 * 
 */
UCLASS()
class MAZEPROJECT3_API AWinTrigger : public APickup
{
	GENERATED_BODY()

public:
	virtual void Collect(APlayerCharacter* p);
	
};
