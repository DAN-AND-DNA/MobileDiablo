// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloItem.h"
#include "Assets/MobileDiabloHeroAsset.h"
#include "MobileDiabloCharacter.h"
#include "MobileDiabloMapCacheSubsystem.h"
#include "Components/CapsuleComponent.h"
#include "Items/MobileDiabloEquipment.h"
#include "Items/MobileDiabloWeapon.h"


AMobileDiabloItem::AMobileDiabloItem() {
	PrimaryActorTick.bCanEverTick = true;

	this->CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	this->SetRootComponent(this->CapsuleComp);
	this->CapsuleComp->SetCollisionProfileName("Item");
	
	this->SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	this->SkeletalMeshComp->SetupAttachment(this->CapsuleComp);
	this->SkeletalMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->SkeletalMeshComp->PrimaryComponentTick.bCanEverTick = false;
	
	this->StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	this->StaticMeshComp->SetupAttachment(this->CapsuleComp);
	this->StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->StaticMeshComp->PrimaryComponentTick.bCanEverTick = false;

	switch (this->ItemType) {
	case EMobileDiabloItemType::EEquipment:
		{
			this->SkeletalMeshComp->PrimaryComponentTick.bCanEverTick = true;
			break;
		}
	case EMobileDiabloItemType::EWeapon:
		{
			this->StaticMeshComp->PrimaryComponentTick.bCanEverTick = true;
			break;
		}
	default:
		break;
	}
}

FText AMobileDiabloItem::GetInteractText_Implementation(AMobileDiabloCharacter* InstigatorCharacter) {
	return FText::FromString(TEXT("按E拾取"));
}

void AMobileDiabloItem::Interact_Implementation(AMobileDiabloCharacter* InstigatorCharacter) {
	UMobileDiabloMapCacheSubsystem* MapCacheSubsystem = this->GetGameInstance()->GetSubsystem<UMobileDiabloMapCacheSubsystem>();
	if (MapCacheSubsystem == nullptr) {
		return;
	}

	UMobileDiabloHeroAsset* HeroAsset = MapCacheSubsystem->GetHeroAsset(InstigatorCharacter->HeroID);
	if (!IsValid(HeroAsset)) {
		return;
	}
	
	switch (this->ItemType) {
	case EMobileDiabloItemType::EEquipment:
		// 直接装备
		UE_LOG(LogTemp, Log, TEXT("============= Equip new equipment"));
		InstigatorCharacter->Equip(Cast<AMobileDiabloEquipment>(this));
		InstigatorCharacter->SetHighlight(HeroAsset->bHighlight, HeroAsset->CustomDepthStencilValue);
		this->Destroy();
	case EMobileDiabloItemType::EWeapon:
		UE_LOG(LogTemp, Log, TEXT("============= Equip new weapon"));
		InstigatorCharacter->Equip(Cast<AMobileDiabloWeapon>(this));
	default:
		break;
	}
	
}

