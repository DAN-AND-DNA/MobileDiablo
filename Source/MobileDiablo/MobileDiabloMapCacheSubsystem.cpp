// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloMapCacheSubsystem.h"

#include "MobileDiabloDefine.h"
#include "Assets/MobileDiabloItemAsset.h"
#include "Assets/MobileDiabloMiscAsset.h"
#include "Assets/MobileDiabloHeroAsset.h"
#include "Engine/AssetManager.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/MobileDiabloMapData.h"

void UMobileDiabloMapCacheSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

void UMobileDiabloMapCacheSubsystem::Deinitialize() {
	Super::Deinitialize();
	this->CleanCache();
}

void UMobileDiabloMapCacheSubsystem::CleanCache() {
	this->ItemAssetCache.Empty();
	this->MiscAssetCache.Empty();
	this->HeroAssetCache.Empty();
	this->LoadedAssetCache.Empty();
}

UMobileDiabloMiscAsset* UMobileDiabloMapCacheSubsystem::GetMiscAsset(const FName& MiscID) {
	if(MiscID.IsNone()) {
		return nullptr;
	}
	
	UMobileDiabloMiscAsset** FoundMiscAsset = MiscAssetCache.Find(MiscID);
	if (FoundMiscAsset == nullptr) {
		return nullptr;
	}

	return *FoundMiscAsset;
}

UMobileDiabloHeroAsset* UMobileDiabloMapCacheSubsystem::GetHeroAsset(const FName& HeroID) {
	if(HeroID.IsNone()) {
		return nullptr;
	}
	
	UMobileDiabloHeroAsset** FoundAsset = this->HeroAssetCache.Find(HeroID);
	if (FoundAsset == nullptr) {
		return nullptr;
	}

	return *FoundAsset;
}

UMobileDiabloItemAsset* UMobileDiabloMapCacheSubsystem::GetItemAsset(const FName& ItemID) {
	if(ItemID.IsNone()) {
		return nullptr;
	}
	
	UMobileDiabloItemAsset** FoundAsset = ItemAssetCache.Find(ItemID);
	if (FoundAsset == nullptr) {
		return nullptr;
	}

	return *FoundAsset;
}


void UMobileDiabloMapCacheSubsystem::LoadingMapResources(const FString& FileName, const FName& MapID) {
	if(FileName.IsEmpty()) {
		return;
	}

	// 同步加载 地图数据清单
	const UDataTable* FromMapTable = LoadObject<UDataTable>(nullptr, *FileName, nullptr,  ELoadFlags::LOAD_Quiet);
	if(FromMapTable == nullptr) {
		this->OnAssetLoaded.ExecuteIfBound(0, 0);
		return;
	}
	
	TArray<FMobileDiabloMapData*> Rows;
	FromMapTable->GetAllRows<FMobileDiabloMapData>("MapAssets", Rows);
	if(Rows.Num() == 0) {
		this->OnAssetLoaded.ExecuteIfBound(0, 0);
		return;
	}
	
	this->CurrentLoadedAssetNum = 0;
	this->NeedLoadAssetNum = Rows.Num();

	// 加载数据
	for (const FMobileDiabloMapData* Row : Rows) {
		if (Row->Asset.IsNull()) {
			continue;
		}

		UPrimaryDataAsset* LoadedAsset = Row->Asset.LoadSynchronous();
		LoadedAssetCache.Add(LoadedAsset->GetPrimaryAssetId(), LoadedAsset);
		UE_LOG(LogTemp, Log, TEXT("============= Loaded Asset: %s"), *(LoadedAsset->GetPrimaryAssetId().ToString()));
		this->OnLoadedPrimaryAsset(LoadedAsset->GetPrimaryAssetId());
	}
}

// 卸载资源
void UMobileDiabloMapCacheSubsystem::UnloadMapResources(const FString& TablePath, const FName& MapID) {
	if(TablePath.IsEmpty()) {
		return;
	}
	
	const UDataTable* MapTable = LoadObject<UDataTable>(nullptr, *TablePath, nullptr, ELoadFlags::LOAD_Quiet);
	if(MapTable == nullptr) {
		return;
	}
	
	TArray<FMobileDiabloMapData*> Rows;
	MapTable->GetAllRows<FMobileDiabloMapData>("MapAssets", Rows);
	if(Rows.Num() == 0) {
		return;
	}

	for (const FMobileDiabloMapData* Row : Rows) {
		if (!MapID.IsNone()) {
			continue;
		}

		if(Row->Asset.IsNull() || Row->Asset.Get() == nullptr) {
			continue;
		}

		UPrimaryDataAsset* LoadedAsset = Row->Asset.Get();
		FPrimaryAssetId	ResourceID = LoadedAsset->GetPrimaryAssetId();
		
		if (ResourceID.PrimaryAssetType == FMobileDiabloDefine::ItemAssetType) {
			const UMobileDiabloItemAsset* ItemAsset = Cast<UMobileDiabloItemAsset> (LoadedAsset);
			this->ItemAssetCache.Remove(ItemAsset->ItemID);
		}

		if (ResourceID.PrimaryAssetType == FMobileDiabloDefine::MiscAssetType) {
			const UMobileDiabloMiscAsset* MiscAsset = Cast<UMobileDiabloMiscAsset> (LoadedAsset);
			this->MiscAssetCache.Remove(MiscAsset->MiscID);
		}

		if (ResourceID.PrimaryAssetType == FMobileDiabloDefine::HeroAssetType) {
			const UMobileDiabloHeroAsset* HeroAsset = Cast<UMobileDiabloHeroAsset>(LoadedAsset);
			this->HeroAssetCache.Remove(HeroAsset->HeroID);
		}

		this->LoadedAssetCache.Remove(ResourceID);
		UE_LOG(LogTemp, Log, TEXT("============= Unloaded Asset: %s"), *(ResourceID.ToString()));
		//if (!Row->AssetID.IsValid()) {
		//	continue;
		//}
		
		//UE_LOG(LogTemp, Log, TEXT("============= Unloaded Asset: %s"), *(Row->AssetID.ToString()));
		//AssetManager->UnloadPrimaryAsset(Row->AssetID);
		//AssetManager->RefreshAssetData();
		
		//if(AssetManager->GetPrimaryAssetObject(Row->AssetID) == nullptr) {
		//	UE_LOG(LogTemp, Log, TEXT("============= Unload Asset: %s ok"), *(Row->AssetID.ToString()));
		//} else {
		//	UE_LOG(LogTemp, Log, TEXT("============= Unload Asset: %s failed"), *(Row->AssetID.ToString()));
		//}
	}
}

void UMobileDiabloMapCacheSubsystem::SetLoadingMap(const FName& InLoadingMapID) {
	this->LoadingMapID = InLoadingMapID;
}

void UMobileDiabloMapCacheSubsystem::GotoMap(const FName& InFromMapID, const FName& InToMapID) {
	if(InToMapID.IsNone() || InToMapID == InFromMapID) {
		return;
	}
	
	//this->CleanCache();
	this->CurrentMapID = InFromMapID;
	this->ToMapID = InToMapID;
	this->bAssetLoaded = false;
	
	UGameplayStatics::OpenLevel(this->GetWorld(), this->LoadingMapID);
}

FString UMobileDiabloMapCacheSubsystem::GetValue(const FString& Key) {
	const FString* FoundValue = this->KVCache.Find(Key);
	if (FoundValue == nullptr)	{
		return FString(TEXT(""));
	}
	
	return *FoundValue;
}

void UMobileDiabloMapCacheSubsystem::SetValue(const FString& Key, const FString& Value) {
	this->KVCache.Add(Key, Value);
}

void UMobileDiabloMapCacheSubsystem::OnLoadedPrimaryAsset (FPrimaryAssetId ResourceID) {
	/*
	const UAssetManager* AssetManager = UAssetManager::GetIfValid();
	if(!IsValid(AssetManager)) {
		return;
	}

	UObject* LoadedAsset = AssetManager->GetPrimaryAssetObject(ResourceID);
	if(!IsValid(LoadedAsset)) {
		return;
	}
	*/

	UPrimaryDataAsset** FoundLoadedAsset = this->LoadedAssetCache.Find(ResourceID);
	if(FoundLoadedAsset == nullptr) {
		return;
	}

	UPrimaryDataAsset* LoadedAsset = *FoundLoadedAsset;
	
	if (ResourceID.PrimaryAssetType == FMobileDiabloDefine::ItemAssetType) {
		// 作为物品添加到缓存中，包括了模型，贴图，声音等
		UMobileDiabloItemAsset* ItemAsset = Cast<UMobileDiabloItemAsset> (LoadedAsset);
		this->ItemAssetCache.Add(ItemAsset->ItemID, ItemAsset);
	}

	if (ResourceID.PrimaryAssetType == FMobileDiabloDefine::MiscAssetType) {
		// 作为杂项添加到缓存中，包括了出生点，传送点
		UMobileDiabloMiscAsset* MiscAsset = Cast<UMobileDiabloMiscAsset> (LoadedAsset);
		this->MiscAssetCache.Add(MiscAsset->MiscID, MiscAsset);
	}

	if (ResourceID.PrimaryAssetType == FMobileDiabloDefine::HeroAssetType) {
		// 作为英雄加载到缓存中
		UMobileDiabloHeroAsset* HeroAsset = Cast<UMobileDiabloHeroAsset>(LoadedAsset);
		this->HeroAssetCache.Add(HeroAsset->HeroID, HeroAsset);
	}
	
	this->CurrentLoadedAssetNum ++;
	this->OnAssetLoaded.ExecuteIfBound(this->NeedLoadAssetNum, this->CurrentLoadedAssetNum);
}
