// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloAction.h"
#include "MobileDiablo/Components/MobileDiabloActionComponent.h"

bool UMobileDiabloAction::CanStart_Implementation(AActor* Instigator) {

	// 是否已经激活或者存在无法激活的限制
	if (this->bIsRunning || this->OwnerActionComp == nullptr || this->OwnerActionComp->HasAny(this->BlockedTags)) {
		return false;
	}
	
	return true;
}

bool UMobileDiabloAction::StartAction_Implementation(AActor* Instigator) {
	
	if (this->OwnerActionComp == nullptr) {
		return false;
	}
	
	// 本UMobileDiabloAction由场景中的对象创建
	const AActor* OuterActor = Cast<AActor> (this->GetOuter());
	if(OuterActor == nullptr) {
		return false;
	}
	
	const UWorld* World = OuterActor->GetWorld();
	if(World == nullptr) {
		return false;
	}
	
	this->OwnerActionComp->AppendTags(this->GrantsTags);
	this->bIsRunning = true;
	this->ActionInstigator = Instigator;
	this->TimeStarted = World->GetTimeSeconds();

	// 通知蓝图
	this->OwnerActionComp->OnActionStart.Broadcast(this->OwnerActionComp, this);
	return true;
}

void UMobileDiabloAction::StopAction_Implementation(AActor* Instigator) {
	if(this->OwnerActionComp == nullptr) {
		return;
	}

	this->OwnerActionComp->RemoveTags(this->GrantsTags);
	this->bIsRunning = false;
	this->ActionInstigator = Instigator;

	this->OwnerActionComp->OnActionStopped.Broadcast(this->OwnerActionComp, this);
}