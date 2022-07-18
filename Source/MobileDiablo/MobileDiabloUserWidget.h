// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MobileDiabloUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEDIABLO_API UMobileDiabloUserWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	class AMobileDiabloPlayerController* OwnerPC;
};
