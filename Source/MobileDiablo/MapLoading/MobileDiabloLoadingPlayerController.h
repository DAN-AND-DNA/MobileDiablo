// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileDiablo/MobileDiabloPlayerController.h"
#include "MobileDiabloLoadingPlayerController.generated.h"

UCLASS(Blueprintable)
class MOBILEDIABLO_API AMobileDiabloLoadingPlayerController : public AMobileDiabloPlayerController {
	GENERATED_BODY()

public:
	AMobileDiabloLoadingPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> LoadingWidgetClass;

	void ShowWidgets();
	
	//virtual void BeginPlay() override;

protected:
	UPROPERTY()
	UUserWidget* LoadingWidgetInst;
};
