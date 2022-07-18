#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/ShowEquipmentPosition.h"
#include "ShowEquipmentInfo.generated.h"

USTRUCT(BlueprintType)
struct FShowEquipmentInfo: public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EShowEquipmentPosition Position;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* Equipment;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* Weapon;
};