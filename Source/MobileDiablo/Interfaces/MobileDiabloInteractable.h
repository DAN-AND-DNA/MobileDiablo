// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MobileDiabloInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMobileDiabloInteractable : public UInterface {
	GENERATED_BODY()
};

/**
 * 
 */
class MOBILEDIABLO_API IMobileDiabloInteractable {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FText GetInteractText(class AMobileDiabloCharacter* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(class AMobileDiabloCharacter* Instigator);
};
