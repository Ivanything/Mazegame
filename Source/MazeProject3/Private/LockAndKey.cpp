// Fill out your copyright notice in the Description page of Project Settings.


#include "LockAndKey.h"

ALockAndKey::ALockAndKey() 
{
	OnActorBeginOverlap.AddDynamic(this, &ALockAndKey::CheckActorType);
}

void ALockAndKey::BeginPlay()
{
	// Made method attached to overlapping trigger event, it's in begin play since it didn't work in the constructor
	OnActorBeginOverlap.AddDynamic(this, &ALockAndKey::CheckActorType);
}

void ALockAndKey::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
{
	OpenTheDoor();// Will "open the door" when triggering anything (right now there is only one thing in the game)
}

void ALockAndKey::OpenTheDoor()
{
	SetActorLocation(FVector(0, 0, -500));// Will spawn the door somewhere underground so you can't see it
	this->Destroy();// This code doesn't work?????



	// Will maybe try again later, but this crashed and broke my project after reopening
	//Cast<AActor>(this)->K2_DestroyActor();
}
