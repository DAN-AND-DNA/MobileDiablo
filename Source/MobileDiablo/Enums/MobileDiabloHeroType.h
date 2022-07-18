#pragma once

#include "CoreMinimal.h"
#include "MobileDiabloHeroType.generated.h"

UENUM()
enum class EMobileDiabloHeroType: uint8 {
	ENone		UMETA(DisplayName = "N/A"),
	EKnight		UMETA(DisplayName = "Knight"),
};
