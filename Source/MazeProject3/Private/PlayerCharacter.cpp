// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	respawnPoint = GetActorLocation();
	OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::Respawn);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Some Message"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerCharacter::Vertical);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerCharacter::Horizontal);
	PlayerInputComponent->BindAxis("MouseX", this, &APlayerCharacter::MouseX);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	//PlayerInputComponent->BindAction("Spawn", IE_Pressed, this, &APlayerCharacter::SpawnBox);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DoesSetInputs"));
}


void APlayerCharacter::Vertical(float value) {
	AddMovementInput(GetActorForwardVector(), value * moveSpeed);
	if (abs(value) > 0.1f && skMesh)
		(*skMesh).SetWorldRotation(FQuat::Slerp((*skMesh).GetRelativeRotation().Quaternion(), (GetActorForwardVector() * value).Rotation().Quaternion(), 10));
}

void APlayerCharacter::Horizontal(float value) {
	AddMovementInput(GetActorRightVector(), value * moveSpeed);
	if (abs(value) > 0.1f && skMesh)
		(*skMesh).SetWorldRotation(FQuat::Slerp((*skMesh).GetRelativeRotation().Quaternion(), (GetActorRightVector() * value).Rotation().Quaternion(), 10));
}

void APlayerCharacter::MouseX(float value) {
	AddControllerYawInput(value * rotationSpeed);
}

void APlayerCharacter::SpawnBox() {
	GetWorld()->SpawnActor<UClass>(ClassForSpawning, GetActorLocation() + GetActorForwardVector() * 100, GetActorRotation());
	
	//This crashes my project for some reason?????
}

void APlayerCharacter::Respawn(class AActor* OverlappedActor, class AActor* OtherActor) {
	if (OtherActor->ActorHasTag("Die")) {
		SetActorLocation(respawnPoint);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You Are Dead!"));
	}
}