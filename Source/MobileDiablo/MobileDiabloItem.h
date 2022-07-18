// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/MobileDiabloItemType.h"
#include "GameFramework/Actor.h"
#include "Interfaces/MobileDiabloInteractable.h"
#include "MobileDiabloItem.generated.h"

UCLASS()
class MOBILEDIABLO_API AMobileDiabloItem : public AActor, public IMobileDiabloInteractable {
	GENERATED_BODY()

public:
	AMobileDiabloItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMobileDiabloItemType ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleComp;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComp;

	virtual FText GetInteractText_Implementation(AMobileDiabloCharacter* InstigatorCharacter) override;

	virtual void Interact_Implementation(AMobileDiabloCharacter* InstigatorCharacter) override;
};
