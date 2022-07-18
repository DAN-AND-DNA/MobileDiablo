// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MobileDiabloSpawnPoint.generated.h"

UCLASS()
class MOBILEDIABLO_API AMobileDiabloSpawnPoint : public AActor {
	GENERATED_BODY()

public:
	AMobileDiabloSpawnPoint();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HeroSlotIndex;
};