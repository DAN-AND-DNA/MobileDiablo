// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloActionComponent.h"
#include "MobileDiablo/Actions/MobileDiabloAction.h"


UMobileDiabloActionComponent::UMobileDiabloActionComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UMobileDiabloActionComponent::AddAction(AActor* Instigator, const TSubclassOf<UMobileDiabloAction>& ActionClass) {
	if(!ActionClass) {
		return;
	}

	// 必须为场景中的对象
	CastChecked<AActor>(this->GetOwner());
	
	UMobileDiabloAction* NewAction = NewObject<UMobileDiabloAction>(this->GetOwner(), ActionClass);
	if(NewAction == nullptr) {
		return;
	}

	NewAction->SetOwnerActionComp(this);
	this->Actions.Add(NewAction);
	
	if(NewAction->bAutoStart && NewAction->CanStart(Instigator)) {
		NewAction->StartAction(Instigator);
	}
}

// 删除但不打断，只删除已经停止的技能
void UMobileDiabloActionComponent::RemoveAction(UMobileDiabloAction* Action) {
	if (Action == nullptr) {
		return;
	}

	if(Action->IsRunning()) {
		return;
	}
	
	this->Actions.Remove(Action);
}

UMobileDiabloAction* UMobileDiabloActionComponent::GetAction(const TSubclassOf<UMobileDiabloAction>& ActionClass) {
	for (UMobileDiabloAction* Action : this->Actions) {
		if(Action == nullptr) {
			continue;
		}

		if(Action->IsA(ActionClass)) {
			return Action;
		}
	}

	return nullptr;
}

bool UMobileDiabloActionComponent::StartActionByID(AActor* Instigator, const FName& InActionID) {
	for (UMobileDiabloAction* Action : this->Actions) {
		if(Action == nullptr || Action->ActionID != InActionID || !Action->CanStart(Instigator)) {
			continue;
		}
		
		Action->StartAction(Instigator);
		return true;
	}

	return false;
}

// 打断技能
bool UMobileDiabloActionComponent::StopActionByID(AActor* Instigator, const FName& InActionID) {
	for (UMobileDiabloAction* Action : this->Actions) {
		if(Action == nullptr || Action->ActionID != InActionID || !Action->IsRunning()) {
			continue;
		}
		
		Action->StopAction(Instigator);
		return true;
	}

	return false;
}

bool UMobileDiabloActionComponent::HasAny(const FGameplayTagContainer& Tags) {
	return this->ActivedTags.HasAny(Tags);
}

void UMobileDiabloActionComponent::AppendTags(const FGameplayTagContainer& Tags) {
	this->ActivedTags.AppendTags(Tags);
}

void UMobileDiabloActionComponent::RemoveTags(const FGameplayTagContainer& Tags) {
	this->ActivedTags.RemoveTags(Tags);
}

