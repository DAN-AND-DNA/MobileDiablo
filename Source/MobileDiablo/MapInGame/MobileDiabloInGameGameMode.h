// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileDiablo/MobileDiabloGameModeBase.h"
#include "MobileDiabloInGameGameMode.generated.h"

UCLASS(Blueprintable)
class MOBILEDIABLO_API AMobileDiabloInGameGameMode : public AMobileDiabloGameModeBase {
	
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AMobileDiabloInGameGameMode();

	virtual void BeginPlay() override;
};
