// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloLoadingPlayerController.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"


AMobileDiabloLoadingPlayerController::AMobileDiabloLoadingPlayerController() {
	PrimaryActorTick.bCanEverTick = true;
}

void AMobileDiabloLoadingPlayerController::ShowWidgets() {
	if(this->LoadingWidgetClass) {
		this->LoadingWidgetInst = CreateWidget(this, this->LoadingWidgetClass);
		this->LoadingWidgetInst->AddToViewport(10);
	}
}
