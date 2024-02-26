// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MAZEPROJECT3_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void myDamage(float d);

	virtual void Die();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
		float moveSpeed;
	UPROPERTY(EditAnywhere)
		float rotationSpeed;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ClassForSpawning;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skMesh;

private:
	FVector respawnPoint;

private:
	void Vertical(float value);
	void Horizontal(float value);
	void MouseX(float value);
	void SpawnBox();
	UFUNCTION()
		void Respawn(class AActor* OverlappedActor, class AActor* OtherActor);

public:
	UPROPERTY(EditAnywhere)
		float maxHealth;

protected:
	float _currentHealth;
};
