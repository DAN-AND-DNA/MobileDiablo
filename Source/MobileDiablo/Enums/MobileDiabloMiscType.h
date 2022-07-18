#pragma once

#include "CoreMinimal.h"
#include "MobileDiabloMiscType.generated.h"

UENUM()
enum class  EMobileDiabloMiscType : uint8 {
	ENone		UMETA(DisplayName = "N/A"),
	ESpawnPoint	UMETA(DisplayName = "SpawnPoint"),
	EShowMove	UMETA(DisplayName = "ShowMove"),
};
