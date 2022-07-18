// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "MobileDiabloActionComponent.generated.h"


UCLASS(ClassGroup=(AfternooTea), meta=(BlueprintSpawnableComponent))
class MOBILEDIABLO_API UMobileDiabloActionComponent : public UActorComponent {
	GENERATED_BODY()
public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStateChanged, UMobileDiabloActionComponent*, OwnerComp, class UMobileDiabloAction*, Action);

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStart;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStopped;
	
	UMobileDiabloActionComponent();

	UFUNCTION(BlueprintCallable)
	void AddAction(AActor* Instigator, const TSubclassOf<class UMobileDiabloAction>& ActionClass);

	UFUNCTION(BlueprintCallable)
	void RemoveAction(class UMobileDiabloAction* Action);

	UFUNCTION(BlueprintCallable)
	UMobileDiabloAction* GetAction(const TSubclassOf<class UMobileDiabloAction>& ActionClass);

	UFUNCTION(BlueprintCallable)
	bool StartActionByID(AActor* Instigator, const FName& InActionID);

	UFUNCTION(BlueprintCallable)
	bool StopActionByID(AActor* Instigator, const FName& InActionID);
	
	bool HasAny(const FGameplayTagContainer& Tags);

	void AppendTags(const FGameplayTagContainer& Tags);

	void RemoveTags(const FGameplayTagContainer& Tags);
protected:
	FGameplayTagContainer ActivedTags;

	UPROPERTY()
	TArray<class UMobileDiabloAction*> Actions;
};
