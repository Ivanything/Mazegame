// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPack.h"


void ASpeedPack::Collect(APlayerCharacter* p) {
	(*p).Sprint(speedTimer);

	this->Destroy();
}