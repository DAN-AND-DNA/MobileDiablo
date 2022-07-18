// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileDiabloMapCacheSubsystem.generated.h"


UCLASS()
class MOBILEDIABLO_API UMobileDiabloMapCacheSubsystem : public UGameInstanceSubsystem {
	GENERATED_BODY()

public:

	DECLARE_DELEGATE_TwoParams(FOnAssetLoaded, float /* total */, float /* loaded */);
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	//UFUNCTION(BlueprintCallable)
	//void AddItemAsset(FName ItemID, class UMobileDiabloItemAsset* ItemAsset);

	//UFUNCTION(BlueprintCallable)
	void CleanCache();

	class UMobileDiabloMiscAsset* UMobileDiabloMapCacheSubsystem::GetMiscAsset(const FName& MiscID);
	class UMobileDiabloItemAsset* UMobileDiabloMapCacheSubsystem::GetItemAsset(const FName& ItemID);
	class UMobileDiabloHeroAsset* UMobileDiabloMapCacheSubsystem::GetHeroAsset(const FName& HeroID);

	void LoadingMapResources(const FString& FileName, const FName& MapID);

	void UnloadMapResources(const FString&  FileName,  const FName& MapID);

	void SetLoadingMap(const FName& LoadingMapID);

	UFUNCTION(BlueprintCallable)
	void GotoMap(const FName& FromMapID, const FName& ToMapID);

	UFUNCTION(BlueprintCallable)
	FString GetValue(const FString& Key);

	UFUNCTION(BlueprintCallable)
	void SetValue(const FString& Key, const FString& Value);

	void OnLoadedPrimaryAsset(FPrimaryAssetId ResourceID);

	FOnAssetLoaded OnAssetLoaded;

	bool bAssetLoaded;
	
	FName CurrentMapID;
	
	FName ToMapID;
private:
	UPROPERTY()
	TMap<FPrimaryAssetId, class UPrimaryDataAsset*> LoadedAssetCache;
	
	UPROPERTY()
	TMap<FName, class UMobileDiabloItemAsset*> ItemAssetCache;

	UPROPERTY()
	TMap<FName, class UMobileDiabloMiscAsset*> MiscAssetCache;

	UPROPERTY()
	TMap<FName, class UMobileDiabloHeroAsset*> HeroAssetCache;

	UPROPERTY()
	TMap<FString, FString>	KVCache;

	int32 NeedLoadAssetNum;
	
	int32 CurrentLoadedAssetNum;

	FName LoadingMapID;
};
