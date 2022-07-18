// Copyright Epic Games, Inc. All Rights Reserved.


#include "MobileDiabloGameModeBase.h"
#include "MobileDiablo/MobileDiabloCharacter.h"
#include "MobileDiabloPlayerController.h"

AMobileDiabloGameModeBase::AMobileDiabloGameModeBase() {
	this->DefaultPawnClass = AMobileDiabloCharacter::StaticClass();
	this->PlayerControllerClass = AMobileDiabloPlayerController::StaticClass();
}
