// Fill out your copyright notice in the Description page of Project Settings.


#include "LockAndKey.h"

ALockAndKey::ALockAndKey() 
{
	OnActorBeginOverlap.AddDynamic(this, &ALockAndKey::CheckActorType);
}

void ALockAndKey::BeginPlay()
{
	OnActorBeginOverlap.AddDynamic(this, &ALockAndKey::CheckActorType);
}

void ALockAndKey::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
{
	OpenTheDoor();
}

void ALockAndKey::OpenTheDoor()
{
	SetActorLocation(FVector(0, 0, -500));// Use this instead of deleting it
	this->Destroy();// This code doesn't work?????



	// Will maybe try again later, but this crashed and broke my project after reopening
	//Cast<AActor>(this)->K2_DestroyActor();
}
