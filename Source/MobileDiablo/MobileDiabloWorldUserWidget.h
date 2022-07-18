// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MobileDiabloWorldUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOBILEDIABLO_API UMobileDiabloWorldUserWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class USizeBox* ParentSizeBox;
	
	FORCEINLINE	void AttachedTo(AActor* WorldActor) { AttachedActor = WorldActor;}

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY()
	AActor*	AttachedActor;

};
