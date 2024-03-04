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
	OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::DamageTrigger);
	if (maxHealth2 == 0)
		maxHealth2 = 20;
	_currentHealth = maxHealth2;
	UE_LOG(LogTemp, Log, TEXT("The player's health starts off at %f."), maxHealth2);

	UE_LOG(LogTemp, Log, TEXT("Health is pointing to %p and Sprinting is pointing to %p"), &maxHealth2, &sprinting);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (damageOnce) return 0;
	myDamage(DamageAmount);
	return DamageAmount;
}

void APlayerCharacter::myDamage(float d)
{
	damageOnce = true;
	_currentHealth -= d;
	UGameplayStatics::PlaySound2D(this, damageSound, 0.5f, 1, 0);
	UE_LOG(LogTemp, Log, TEXT("You have %f health left."), _currentHealth);

	//UE_LOG(LogTemp, Log, TEXT("The player took %f damage and has %f health left and started with %f health."), d, _currentHealth, maxHealth2);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("You Took Damage!"));

	if (_currentHealth <= 0)
		Die();
}

void APlayerCharacter::Die()
{
	GetMesh()->PlayAnimation(deathAnimation, false);
	isRespawning = true;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("You Are Dead!"));
}

void APlayerCharacter::Respawn()
{
	_currentHealth = maxHealth2;
	UE_LOG(LogTemp, Log, TEXT("I now have %f health."), _currentHealth);
	isRespawning = false;
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	SetActorLocation(respawnPoint);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("You Respawned!"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Log, TEXT("Sprinting is at %f."), sprinting);
	damageOnce = false;
	if (sprinting > 0)
		sprinting -= DeltaTime;
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
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DoesSetInputs"));
}


void APlayerCharacter::Vertical(float value) {
	if (isRespawning) return;

	if (sprinting > 0)
		AddMovementInput(GetActorForwardVector(), value * moveSpeed * 10);
	else
		AddMovementInput(GetActorForwardVector(), value * moveSpeed);

	if (abs(value) > 0.1f && skMesh)
		(*skMesh).SetWorldRotation(FQuat::Slerp((*skMesh).GetRelativeRotation().Quaternion(), (GetActorForwardVector() * value).Rotation().Quaternion(), 10));
}

void APlayerCharacter::Horizontal(float value) {
	if (isRespawning) return;

	//UE_LOG(LogTemp, Log, TEXT("Sprinting is at %f."), sprinting);
	if (sprinting > 0) {
		//UE_LOG(LogTemp, Log, TEXT("Am Sprinting"));
		AddMovementInput(GetActorRightVector(), value * moveSpeed * 10);
	}
	else
		AddMovementInput(GetActorRightVector(), value * moveSpeed);

	if (abs(value) > 0.1f && skMesh)
		(*skMesh).SetWorldRotation(FQuat::Slerp((*skMesh).GetRelativeRotation().Quaternion(), (GetActorRightVector() * value).Rotation().Quaternion(), 10));
}

void APlayerCharacter::MouseX(float value) {
	if (isRespawning) return;

	AddControllerYawInput(value * rotationSpeed);
}

void APlayerCharacter::SpawnBox() {
	GetWorld()->SpawnActor<UClass>(ClassForSpawning, GetActorLocation() + GetActorForwardVector() * 100, GetActorRotation());
	
	//This crashes my project for some reason????? Ignore this
}

// Will spawn you back to the beginning when you trigger something that has the "Die" tag
void APlayerCharacter::DamageTrigger(class AActor* OverlappedActor, class AActor* OtherActor) {
	if (OtherActor->ActorHasTag("Die")) {
		FVector launch = OverlappedActor->GetActorLocation() - OtherActor->GetActorLocation();
		launch.Normalize();
		launch += FVector(0, 0, 0.5f);
		launch.Normalize();
		GetCharacterMovement()->AddImpulse(launch * -1000, true);
		myDamage(5);
	}
}

void APlayerCharacter::Heal(float h) {
	_currentHealth += h;
	if (_currentHealth > maxHealth2)
		_currentHealth = maxHealth2;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("You were HEALED!"));
	UE_LOG(LogTemp, Log, TEXT("Your health is now %f."), _currentHealth);
}

void APlayerCharacter::Sprint(float s) {
	//sprinting = s;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("You have SPEED!!! \n(3 seconds)"));
}
