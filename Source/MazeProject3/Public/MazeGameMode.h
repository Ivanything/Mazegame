// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/DefaultPawn.h"
#include "MazeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MAZEPROJECT3_API AMazeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void InitGameState() override;

private:
	UPROPERTY(EditAnywhere, NoClear)
	TSubclassOf<APlayerCharacter> DefaultPlayerCharacter = APlayerCharacter::StaticClass();
};
