// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileDiablo/MobileDiabloPlayerController.h"
#include "MobileDiabloMainMenuPlayerController.generated.h"

UCLASS(Blueprintable)
class MOBILEDIABLO_API AMobileDiabloMainMenuPlayerController : public AMobileDiabloPlayerController
{
	GENERATED_BODY()
public:
	AMobileDiabloMainMenuPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> MainMenuClass;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	UPARAM(DisplayName = "ClosestTarget")  AActor* GetClosestTarget(bool bDebugDraw = false, float Radius = 100);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	class UUserWidget* MainMenuInst;
};
