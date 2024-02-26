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
	// Setting the respawn point to respawn you and making the trigger enter call my function
	respawnPoint = GetActorLocation();
	OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::Respawn);
	_currentHealth = maxHealth;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Some Message"));
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	myDamage(DamageAmount);
	return DamageAmount;
}

void APlayerCharacter::myDamage(float d)
{
	_currentHealth -= d;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("The player took %f damage and has %f health left.", d, _currentHealth));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("You Took Damage!"));

	if (_currentHealth <= 0)
		Die();
}

void APlayerCharacter::Die()
{
	SetActorLocation(respawnPoint);
	_currentHealth = maxHealth;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You Are Dead!"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Binding all the actions to the correct functions
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
	
	//This crashes my project for some reason????? Ignore this
}

// Will spawn you back to the beginning when you trigger something that has the "Die" tag
void APlayerCharacter::Respawn(class AActor* OverlappedActor, class AActor* OtherActor) {
	if (OtherActor->ActorHasTag("Die")) {
		FVector launch = OtherActor->GetActorLocation() - OverlappedActor->GetActorLocation();
		launch.Normalize();
		launch += FVector(0, 0, 0.5f);
		launch.Normalize();
		GetCharacterMovement()->AddImpulse(launch * -1000, true);
		myDamage(5);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Don't Hit That!"));
	}
}