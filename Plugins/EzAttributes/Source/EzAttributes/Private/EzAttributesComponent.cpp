// Fill out your copyright notice in the Description page of Project Settings.


#include "EzAttributesComponent.h"

UEzAttributesComponent::UEzAttributesComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UEzAttributesComponent::Register(const FString& AttributeName, float CurrentValue, float MaxValue, float MinValue, AActor* Instigator) {
	if (this->Attributes.Contains(AttributeName)) {
		return;
	}

	if(MaxValue < 0.f) {
		MaxValue = 0.f;
	}

	if(MinValue < 0.f) {
		MinValue = 0.f;
	}

	if (MinValue > MaxValue) {
		MinValue = MaxValue;
	}

	CurrentValue = FMath::Clamp(CurrentValue, MinValue, MaxValue);
	
	
	FEzAttribute NewAttribute;
	NewAttribute.CurrentValue = CurrentValue;
	NewAttribute.MaxValue = MaxValue;
	NewAttribute.MinValue = MinValue;
	this->Attributes.Add(AttributeName, NewAttribute);
	
	// notify native & bp
	this->OnAttributeChanged_Native.ExecuteIfBound(EEzAttributesChangedType::ERegistered, Instigator, -1.f, -1.f);
	this->OnAttributeChanged_BP.Broadcast(EEzAttributesChangedType::ERegistered, Instigator, -1.f, -1.f);
}

void UEzAttributesComponent::Remove(const FString& AttributeName, AActor* Instigator) {
	if (!this->Attributes.Contains(AttributeName)) {
		return;
	}

	this->Attributes.Remove(AttributeName);
	
	// notify native & bp
	this->OnAttributeChanged_Native.ExecuteIfBound(EEzAttributesChangedType::ERemoved, Instigator, -1.f, -1.f);
	this->OnAttributeChanged_BP.Broadcast(EEzAttributesChangedType::ERemoved, Instigator, -1.f, -1.f);
}

void UEzAttributesComponent::Change(const FString& AttributeName, float Delta, AActor* Instigator) {
	FEzAttribute* OldAttribute	= this->Attributes.Find(AttributeName);

	if (OldAttribute == nullptr) {
		return;
	}
	
	OldAttribute->CurrentValue = FMath::Clamp(OldAttribute->CurrentValue, OldAttribute->MinValue, OldAttribute->MaxValue);

	// notify native & bp
	this->OnAttributeChanged_Native.ExecuteIfBound(EEzAttributesChangedType::EValueChanged, Instigator, OldAttribute->CurrentValue, Delta);
	this->OnAttributeChanged_BP.Broadcast(EEzAttributesChangedType::EValueChanged, Instigator, OldAttribute->CurrentValue , Delta);
}

bool UEzAttributesComponent::Get(const FString& InAttributeName,  FEzAttribute& OutAttribute) const {
	if (!this->Attributes.Contains(InAttributeName)) {
		return false;
	}

	const FEzAttribute* FoundAttribute = this->Attributes.Find(InAttributeName);
	if(FoundAttribute == nullptr) {
		return false;
	}

	// copy one
	FEzAttribute TmpAttribute = *FoundAttribute;
	
	OutAttribute = MoveTemp(TmpAttribute);
	return true;
}
