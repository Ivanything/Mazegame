// Fill out your copyright notice in the Description page of Project Settings.


#include "OneUp.h"


void AOneUp::Collect(APlayerCharacter* p) {
	UGameplayStatics::PlaySound2D(p, sound, 1, 1, 0);
	GiveExtraLife();
	this->Destroy();
}