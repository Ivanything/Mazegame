// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxPhysics.h"

// Sets default values
ABoxPhysics::ABoxPhysics()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoxPhysics::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxPhysics::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

