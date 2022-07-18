// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MobileDiabloInteractionComponent.generated.h"


UCLASS(ClassGroup=(AfternoonTea), meta=(BlueprintSpawnableComponent))
class MOBILEDIABLO_API UMobileDiabloInteractionComponent : public UActorComponent{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMobileDiabloInteractionComponent();

	FORCEINLINE	AActor* GetNearestTarget() const {return NearestTarget;}
	
protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte <ECollisionChannel> TraceChannel;

	UPROPERTY(BlueprintReadOnly)
	AActor* NearestTarget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UMobileDiabloWorldUserWidget> WorldUserWidgetClass;
	
	UPROPERTY()
	class UMobileDiabloWorldUserWidget* WorldUserWidgetInst;
};
