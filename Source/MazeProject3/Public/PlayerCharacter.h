// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
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

	bool damageOnce = false;

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
	UPROPERTY(EditAnywhere)
		UAnimSequence* deathAnimation;
	UPROPERTY(EditAnywhere)
		USoundBase* damageSound;
	UFUNCTION(BlueprintCallable)
		void Respawn();

	void Heal(float h);
	void Sprint(float s);

private:
	FVector respawnPoint;
	bool isRespawning;
	float sprinting;
	UFUNCTION()
		void DamageTrigger(class AActor* OverlappedActor, class AActor* OtherActor);

private:
	void Vertical(float value);
	void Horizontal(float value);
	void MouseX(float value);
	void SpawnBox();

public:
	UPROPERTY(EditAnywhere)
		float maxHealth2;

protected:
	float _currentHealth;
};
