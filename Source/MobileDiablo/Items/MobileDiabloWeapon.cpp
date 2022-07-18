// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloWeapon.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "MobileDiablo/MobileDiabloCharacter.h"


// Sets default values
AMobileDiabloWeapon::AMobileDiabloWeapon() {
	PrimaryActorTick.bCanEverTick = true;
	this->ItemType = EMobileDiabloItemType::EWeapon;
}

void AMobileDiabloWeapon::BeginPlay() {
	Super::BeginPlay();
}

void AMobileDiabloWeapon::AttachedTo(AMobileDiabloCharacter* OwnerCharacter, const FName& ScoketName) {
	if(!IsValid(OwnerCharacter)) {
		return;
	}
	
	// 调整碰撞
	this->CapsuleComp->SetCollisionProfileName("Weapon");
	this->CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	this->AttachToComponent(OwnerCharacter->GetMesh(), Rules, ScoketName);
}


