// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MobileDiablo/MobileDiabloItem.h"
#include "MobileDiabloWeapon.generated.h"

UCLASS()
class MOBILEDIABLO_API AMobileDiabloWeapon : public AMobileDiabloItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMobileDiabloWeapon();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ActionID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UMobileDiabloAction> ActionClass;
	

	UFUNCTION()
	void AttachedTo(AMobileDiabloCharacter* OwnerCharacter, const FName& ScoketName);
};
