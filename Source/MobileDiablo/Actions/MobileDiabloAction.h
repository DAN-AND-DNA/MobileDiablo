// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "MobileDiabloAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MOBILEDIABLO_API UMobileDiabloAction : public UObject {
	GENERATED_BODY()

public:
	FORCEINLINE void SetOwnerActionComp(class UMobileDiabloActionComponent* ActionComp) { this->OwnerActionComp = ActionComp;}

	FORCEINLINE UMobileDiabloActionComponent* GetOwnerActionComp() {return this->OwnerActionComp;}

	UPROPERTY(EditDefaultsOnly)
	bool bAutoStart;

	UPROPERTY(EditDefaultsOnly)
	FName ActionID;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE	bool IsRunning() const {return bIsRunning;}
	
	UFUNCTION(BlueprintNativeEvent)
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent)
	bool StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent)
	void StopAction(AActor* Instigator);
	
protected:
	UPROPERTY()
	class UMobileDiabloActionComponent* OwnerActionComp;

	bool bIsRunning;

	UPROPERTY()
	AActor* ActionInstigator;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer BlockedTags;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer GrantsTags;

	float TimeStarted;
};
