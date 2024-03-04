// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &APickup::Trigger);
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::Trigger(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		Collect(Cast<APlayerCharacter>(OtherActor));
}

void APickup::Collect(APlayerCharacter* p) {
	//Nothing here for the generic Pickup Script, will be overriden by child classes
}