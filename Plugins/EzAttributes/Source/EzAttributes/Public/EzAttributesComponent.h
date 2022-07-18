// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Enums/EzAttributesChangedType.h"
#include "Structs/EzAttribute.h"
#include "EzAttributesComponent.generated.h"


UCLASS(ClassGroup=(AfternoonTea), meta=(BlueprintSpawnableComponent))
class EZATTRIBUTES_API UEzAttributesComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UEzAttributesComponent();

	DECLARE_DELEGATE_FourParams(FOnAttributeChanged_Native, EEzAttributesChangedType /*ChangedType*/, AActor* /*Instigator*/, float /*CurrentValue*/, float /*Delta*/);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged_BP, EEzAttributesChangedType, ChangedType, AActor*, Instigator, float, CurrentValue, float, Delta);
	
	FOnAttributeChanged_Native OnAttributeChanged_Native;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged_BP OnAttributeChanged_BP;

	// register attribute
	UFUNCTION(BlueprintCallable)
	void Register(const FString& AttributeName, float CurrentValue, float MaxValue, float MinValue = 0, class AActor* Instigator = nullptr);

	// remove attribute
	UFUNCTION(BlueprintCallable)
	void Remove(const FString& AttributeName, class AActor* Instigator = nullptr);

	// change value 
	UFUNCTION(BlueprintCallable)
	void Change(const FString& AttributeName, float Delta, class AActor* Instigator = nullptr);

	// get value 
	UFUNCTION(BlueprintCallable)
	bool Get(const FString& InAttributeName, FEzAttribute& OutAttribute) const;

protected:
	TMap<FString, FEzAttribute> Attributes;
};
