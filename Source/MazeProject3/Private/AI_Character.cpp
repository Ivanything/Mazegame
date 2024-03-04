// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character.h"

// Sets default values
AAI_Character::AAI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAI_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAI_Character::ShootGrenade()
{
	FVector pos = GetActorLocation() + FVector(0, 0, 150);
	FRotator rot = GetActorRotation();
	AActor* gren = GetWorld()->SpawnActor(grenadeClass, &(pos), &rot);//FName("Grenade!"), 
}

