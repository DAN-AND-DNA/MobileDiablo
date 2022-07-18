#include "MobileDiabloMainMenuGameMode.h"
#include "MobileDiabloMainMenuPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MobileDiablo/MobileDiabloMapCacheSubsystem.h"
#include "MobileDiablo/MobileDiabloSpawnPoint.h"
#include "MobileDiablo/Assets/MobileDiabloHeroAsset.h"
#include "MobileDiablo/Assets/MobileDiabloMiscAsset.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "MobileDiablo/Enums/MobileDiabloMiscType.h"
#include "MobileDiablo/Assets/MobileDiabloItemAsset.h"
#include "MobileDiablo/MobileDiabloItem.h"
#include "MobileDiablo/Items/MobileDiabloEquipment.h"


AMobileDiabloMainMenuGameMode::AMobileDiabloMainMenuGameMode() {
	this->DefaultPawnClass = nullptr;
	this->PlayerControllerClass = AMobileDiabloMainMenuPlayerController::StaticClass();
}

void AMobileDiabloMainMenuGameMode::BeginPlay() {
	Super::BeginPlay();

	UMobileDiabloMapCacheSubsystem* MapCacheSubsystem = this->GetGameInstance()->GetSubsystem<UMobileDiabloMapCacheSubsystem>();
	if (MapCacheSubsystem == nullptr) {
		return;
	}

	for	(const FName& HeroID: this->HeroIDs)
	{
		// 1. 拿角色信息
		UMobileDiabloHeroAsset* HeroAsset = MapCacheSubsystem->GetHeroAsset(HeroID);
		if(HeroAsset == nullptr || !HeroAsset->HeroClass ) {
			continue;
		}

	
		// 2. 拿主菜单对应的出生位置
		UMobileDiabloMiscAsset* MiscAsset = MapCacheSubsystem->GetMiscAsset(SpawnPointMiscID);
		if (MiscAsset == nullptr || MiscAsset->MiscType != EMobileDiabloMiscType::ESpawnPoint || !MiscAsset->MiscClass) {
			continue;;
		}
	
		FActorSpawnParameters Parameters;
		Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform ItemPosition(FVector(0,0,-1000));
	
		for (TActorIterator<AMobileDiabloSpawnPoint> It(this->GetWorld()); It; ++It) {
			if (HeroAsset->HeroSlotIndex == (*It)->HeroSlotIndex)	{
				const FTransform SpawnPointPosition = (*It)->GetActorTransform();
				// 3. 创建
			
				UE_LOG(LogTemp, Log, TEXT("============= Spawn Hero: %s At slot: %d"), *HeroAsset->HeroID.ToString() , HeroAsset->HeroSlotIndex );
				AMobileDiabloCharacter* SpawnedHero = Cast <AMobileDiabloCharacter> (this->GetWorld()->SpawnActor(HeroAsset->HeroClass, &SpawnPointPosition, Parameters));
				if (!IsValid(SpawnedHero)) {
					continue;
				}
				SpawnedHero->HeroID = HeroAsset->HeroID;
			
				this->GetWorld()->GetFirstPlayerController()->Possess(SpawnedHero);
			
				for	(const FName& StartItemID : HeroAsset->DefaultStartItems)	{
					UMobileDiabloItemAsset* ItemAsset = MapCacheSubsystem->GetItemAsset(StartItemID);
					if(ItemAsset == nullptr) {
						continue;
					}

					// 作为装备
					if (ItemAsset->ItemType == EMobileDiabloItemType::EEquipment)	{
						
					
						AMobileDiabloEquipment* NewEquipment = Cast<AMobileDiabloEquipment> (this->GetWorld()->SpawnActor(ItemAsset->ItemClass, &ItemPosition, Parameters));
						if (NewEquipment == nullptr) {
							continue;
						}
					
						UE_LOG(LogTemp, Log, TEXT("============= Spawn An New Equipment: %s"), *(ItemAsset->ItemID.ToString()));
						// 初始身体
						SpawnedHero->Equip(NewEquipment);
						NewEquipment->Destroy();
					}
					// 是否要遮挡高亮
					SpawnedHero->SetHighlight(HeroAsset->bHighlight, HeroAsset->CustomDepthStencilValue);
				
					// TODO 作为药水
					if (ItemAsset->ItemType == EMobileDiabloItemType::EPotion) {
					
					}
				}
			}
		}
	}

}
