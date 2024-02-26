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
	OnActorBeginOverlap.AddDynamic(this, &ABoxPhysics::DestroySelf);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Does begin"));
	
}

// Called every frame
void ABoxPhysics::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoxPhysics::DestroySelf(class AActor* OverlappedActor, class AActor* OtherActor) {
	this->Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Is trying to destroy self"));
}
