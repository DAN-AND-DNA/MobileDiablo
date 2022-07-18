// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileDiablo/MobileDiabloCharacter.h"
#include "MobileDiabloHeroAsset.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEDIABLO_API UMobileDiabloHeroAsset : public UPrimaryDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName HeroID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMobileDiabloCharacter> HeroClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> DefaultStartItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HeroSlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHighlight;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CustomDepthStencilValue;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
