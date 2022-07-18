// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloPlayerController.h"


AMobileDiabloPlayerController::AMobileDiabloPlayerController() {
	PrimaryActorTick.bCanEverTick = true;

	this->SetShowMouseCursor(true);
	this->bEnableClickEvents = true;
}

//void AMobileDiabloPlayerController::GetHorverTarget() {}
