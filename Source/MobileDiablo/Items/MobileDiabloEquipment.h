// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/ShowEquipmentPosition.h"
#include "MobileDiablo/MobileDiabloItem.h"
#include "MobileDiabloEquipment.generated.h"

UCLASS(Blueprintable)
class MOBILEDIABLO_API AMobileDiabloEquipment : public AMobileDiabloItem {
	GENERATED_BODY()

public:
	AMobileDiabloEquipment();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EShowEquipmentPosition Position;
};
