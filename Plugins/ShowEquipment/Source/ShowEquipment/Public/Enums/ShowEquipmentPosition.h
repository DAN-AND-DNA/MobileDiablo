#pragma once

#include "CoreMinimal.h"
#include "ShowEquipmentPosition.generated.h"


UENUM(BlueprintType)
enum class EShowEquipmentPosition : uint8 {
	ENone			UMETA(DisplayName="N/A"),
	
	EHead			UMETA(DisplayName="Head"),
	EBody			UMETA(DisplayName="Body"),
	
	ELeftArm		UMETA(DisplayName="LeftArm"),
	ELeftHand		UMETA(DisplayName="LeftHand"),
	ELeftLeg		UMETA(DisplayName="LeftLeg"),
	ELeftFeet		UMETA(DisplayName="LeftFeet"),
	
	ERightArm		UMETA(DisplayName="RightArm"),
	ERightHand		UMETA(DisplayName="RightHand"),
	ERightLeg		UMETA(DisplayName="RightLeg"),
	ERightFeet		UMETA(DisplayName="RightFeet"),
};
