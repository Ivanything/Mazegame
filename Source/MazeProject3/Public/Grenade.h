// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI_Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "Grenade.generated.h"

UCLASS()
class MAZEPROJECT3_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
		void setVariables();

	bool doOnce = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* hitSpot;

	UPROPERTY(EditAnywhere)
		float speed = 2000.0;

	UPROPERTY(EditAnywhere)
		float explosionRadius = 2000.0;

	UPROPERTY(EditAnywhere)
		float damage = 5;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* particle;

	UFUNCTION()
		void doExplosion(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
