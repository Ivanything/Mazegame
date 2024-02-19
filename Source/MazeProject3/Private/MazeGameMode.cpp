// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGameMode.h"

void AMazeGameMode::InitGameState()
{
	Super::InitGameState();

	if (DefaultPawnClass == ADefaultPawn::StaticClass()) 
	{
		DefaultPawnClass = DefaultPlayerCharacter;
	}
}