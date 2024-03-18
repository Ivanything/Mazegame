// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MazeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MAZEPROJECT3_API UMazeSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		int highestLevel;
	UPROPERTY(EditAnywhere)
		float masterVol;
	UPROPERTY(EditAnywhere)
		float musicVol;
	UPROPERTY(EditAnywhere)
		float sfxVol;
};
