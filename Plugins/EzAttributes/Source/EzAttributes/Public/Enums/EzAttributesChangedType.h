#pragma once

#include "CoreMinimal.h"
#include "EzAttributesChangedType.generated.h"

UENUM(BlueprintType)
enum class EEzAttributesChangedType : uint8 {
	ENone			UMETA("N/A"),
	ERegistered		UMETA("Registered"),
	ERemoved		UMETA("Removed"),
	EValueChanged	UMETA("ValueChanged"),
};
