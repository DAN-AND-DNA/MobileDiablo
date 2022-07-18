// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileDiablo/MobileDiabloGameModeBase.h"
#include "MobileDiabloLoadingGameMode.generated.h"

/*
* "loading map" game mode
* 1. asset manager load resources from disk
* 2. go to "in game map"
*/
UCLASS(Blueprintable)
class MOBILEDIABLO_API AMobileDiabloLoadingGameMode : public AMobileDiabloGameModeBase {
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FShowProgressDelegate, float, Total, float, Current);
	
	AMobileDiabloLoadingGameMode();

	virtual void BeginPlay() override;

	void ShowProgress(float TotalNum , float CurrentNum);

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FShowProgressDelegate ShowProgressDelegate;
	
	UFUNCTION(BlueprintCallable)
	void GotoNextLevel();
protected:
	
	
	FTimerHandle TimeToChangeLevel;
};
