// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MobileDiabloItemsData.generated.h"

USTRUCT()
struct FMobileDiabloItemsData: public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemID; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId AssetID;
};
