// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileDiabloItemType.generated.h"

UENUM(BlueprintType)
enum class EMobileDiabloItemType : uint8 {
	ENone			UMETA(DisplayName = "N/A"),
	EPotion			UMETA(DisplayName = "Potion"),
	EWeapon			UMETA(DisplayName = "Weapon"),
	EEquipment		UMETA(DisplayName = "Equipment"),
};
