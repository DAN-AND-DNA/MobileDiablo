// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileDiablo/MobileDiabloSpawnPoint.h"
#include "MobileDiablo/Enums/MobileDiabloMiscType.h"
#include "MobileDiabloMiscAsset.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEDIABLO_API UMobileDiabloMiscAsset : public UPrimaryDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MiscID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMobileDiabloMiscType MiscType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AActor> MiscClass;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
