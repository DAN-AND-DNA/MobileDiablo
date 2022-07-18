// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/ShowEquipmentPosition.h"
#include "MobileDiablo/Enums/MobileDiabloItemType.h"
#include "MobileDiabloItemAsset.generated.h"

UCLASS()
class UMobileDiabloItemAsset : public UPrimaryDataAsset {
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AMobileDiabloItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMobileDiabloItemType ItemType;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
