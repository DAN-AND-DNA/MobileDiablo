// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileDiablo/MobileDiabloPlayerController.h"
#include "MobileDiablo/MobileDiabloUserWidget.h"
#include "MobileDiabloInGamePlayerController.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MOBILEDIABLO_API AMobileDiabloInGamePlayerController : public AMobileDiabloPlayerController {
	GENERATED_BODY()
public:
	AMobileDiabloInGamePlayerController();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ShowMoveID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMobileDiabloUserWidget> HUDClass;
protected:
	UPROPERTY()
	UMobileDiabloUserWidget* HUDInst;
	
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;
	
	void OnMouseDown();

	void OnMouseUp();

	void InteractWithItem();

	void TestAction();

	void SetWalkDest();

	bool DistanceToWalkDest(const AActor* Actor, float& Distance, FVector& Direction) const;

	void MoveToWalkDest();

	bool bMouseDown;

	FVector WalkDest;
	
	bool bIsWalking;

	UPROPERTY(BlueprintReadOnly)
	class AMobileDiabloCharacter* CachedHero;
};
