// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"


void AHealthPack::Collect(APlayerCharacter* p) {
	(*p).Heal(healthAmount);

	UGameplayStatics::PlaySound2D(p, sound, 1, 1, 0);

	this->Destroy();
}