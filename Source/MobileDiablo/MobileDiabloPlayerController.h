// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileDiabloPlayerController.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MOBILEDIABLO_API AMobileDiabloPlayerController : public APlayerController {
	GENERATED_BODY()

public:
	AMobileDiabloPlayerController();

	// UFUNCTION(BlueprintCallable)
	// void GetClosestTarget();
};
