// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "PlayerCharacter.h"
#include "LockAndKey.generated.h"

/**
 * 
 */
UCLASS()
class MAZEPROJECT3_API ALockAndKey : public ATriggerBox
{
	GENERATED_BODY()

public:
	ALockAndKey();
	virtual void BeginPlay() override;

	UFUNCTION()
		void CheckActorType(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		void OpenTheDoor();
};
