// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"

// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
}

void AGrenade::setVariables()
{
	hitSpot->OnComponentHit.AddDynamic(this, &AGrenade::doExplosion);
	hitSpot->AddImpulse(GetActorForwardVector() * speed);
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrenade::doExplosion(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitR)
{
	if (doOnce) return;
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), particle, hitSpot->GetComponentLocation(), FRotator());
	doOnce = true;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	TArray<FHitResult> HitArray;
	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), hitSpot->GetComponentLocation(), hitSpot->GetComponentLocation(), 
		explosionRadius, UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::None, HitArray, true, 
		FLinearColor::Red, FLinearColor::Green, 2.0f);

	// If you hit anything, apply damage and apply a force if it is a physics object
	if (Hit) {
		for (const FHitResult hitResult : HitArray) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I just hit " + hitResult.GetActor()->GetName()));//, hitResult.GetActor()->GetName());
			UGameplayStatics::ApplyDamage(hitResult.GetActor(), damage, NULL, this, UDamageType::StaticClass());
			if (hitResult.GetActor()->IsRootComponentMovable() && hitResult.GetComponent()->IsA(UStaticMeshComponent::StaticClass())) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("physics"));
				FVector direction = hitResult.GetComponent()->GetComponentLocation() - hitSpot->GetComponentLocation();
				direction.Normalize();
				direction += FVector(0, 0, 0.7f);//FVector(0, 0, 1000)
				Cast<UStaticMeshComponent>(hitResult.GetComponent())->AddImpulse(direction * 800, NAME_None, true);
			}
			/*else if (hitResult.GetActor()->IsA(APlayerCharacter::StaticClass())) {
				(Cast<APlayerCharacter>(hitResult.GetActor()))->DamageTrigger(Cast<AActor>(this), hitResult.GetActor());
			}*/
		}
	}

	this->Destroy();
}