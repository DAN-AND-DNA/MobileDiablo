// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloInGameGameMode.h"
#include "MobileDiabloInGamePlayerController.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "MobileDiablo/MobileDiabloMapCacheSubsystem.h"
#include "MobileDiablo/Assets/MobileDiabloHeroAsset.h"
#include "MobileDiablo/Assets/MobileDiabloItemAsset.h"
#include "MobileDiablo/Items/MobileDiabloEquipment.h"


AMobileDiabloInGameGameMode::AMobileDiabloInGameGameMode() {
	PrimaryActorTick.bCanEverTick = true;
	this->DefaultPawnClass = nullptr;
	this->PlayerControllerClass = AMobileDiabloInGamePlayerController::StaticClass();
}

void AMobileDiabloInGameGameMode::BeginPlay() {
	Super::BeginPlay();
	
	UMobileDiabloMapCacheSubsystem* MapCacheSubsystem = this->GetGameInstance()->GetSubsystem<UMobileDiabloMapCacheSubsystem>();
	if (MapCacheSubsystem == nullptr) {
		return;
	}
	
	// TODO 从 map cache 拿英雄信息在 start point 生成
	const FString KeyMainMenuSelectedHeroID (TEXT("Key_MainMenu_SelectedHeroID"));
	FString	ValueMainMenuSelectedHeroID = MapCacheSubsystem->GetValue(KeyMainMenuSelectedHeroID);
	if (ValueMainMenuSelectedHeroID.IsEmpty())	{
		return;
	}	

	const FName SelectedHeroID(ValueMainMenuSelectedHeroID);
	const UMobileDiabloHeroAsset* HeroAsset = MapCacheSubsystem->GetHeroAsset(SelectedHeroID);
	if (HeroAsset == nullptr) {
		return;
	}
	
	FTransform StartPosition;
	for( TActorIterator<APlayerStart> It(this->GetWorld()); It; ++It ) {
		StartPosition = (*It)->GetActorTransform();
		break;
	}
	
	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AMobileDiabloCharacter* NewHero = Cast<AMobileDiabloCharacter> (this->GetWorld()->SpawnActor(HeroAsset->HeroClass, &StartPosition, Parameters));
	if (!IsValid(NewHero)) {
		return;
	}

	NewHero->HeroID = SelectedHeroID;
	this->GetWorld()->GetFirstPlayerController()->Possess(NewHero);
	
	FTransform ItemPosition(FVector(0,0,-1000));
	for (const FName& StartItemID  : HeroAsset->DefaultStartItems) {
		UMobileDiabloItemAsset* Item = 	MapCacheSubsystem->GetItemAsset(StartItemID);
		if(Item == nullptr)	{
			continue;
		}
		
		if (Item->ItemType != EMobileDiabloItemType::EEquipment) {
			continue;
		}

		AMobileDiabloEquipment* NewEquipment = Cast<AMobileDiabloEquipment> (this->GetWorld()->SpawnActor(Item->ItemClass, &ItemPosition, Parameters));
		NewHero->Equip(NewEquipment);
		NewEquipment->Destroy();
	}

	NewHero->SetHighlight(HeroAsset->bHighlight, HeroAsset->CustomDepthStencilValue);
	// TODO 在spawn point生成物品 、武器和怪物

	// TODO 英雄可以和物品碰撞交互，比如按E装备之类，靠近出现提示
}
