// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MobileDiabloAnimInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MOBILEDIABLO_API UMobileDiabloAnimInstance : public UAnimInstance {
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY()
	class AMobileDiabloCharacter* Owner;
	
	UPROPERTY(BlueprintReadOnly)
	bool bAccelerated;
	
	UPROPERTY(BlueprintReadOnly)
	float Speed2D;

	UPROPERTY(BlueprintReadOnly)
	bool bAlive;

	UPROPERTY(BlueprintReadOnly)
	float Health;

};
