// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloLoadingGameMode.h"

#include "MobileDiabloLoadingPlayerController.h"
#include "MobileDiablo/MobileDiabloMapCacheSubsystem.h"
#include "Kismet/GameplayStatics.h"



AMobileDiabloLoadingGameMode::AMobileDiabloLoadingGameMode() {
	PrimaryActorTick.bCanEverTick = true;

	this->PlayerControllerClass = AMobileDiabloLoadingPlayerController::StaticClass();
}

void AMobileDiabloLoadingGameMode::BeginPlay() {
	Super::BeginPlay();

	// 1. create and show ui widgets
	AMobileDiabloLoadingPlayerController* LoadingPlayerControler = Cast<AMobileDiabloLoadingPlayerController>(this->GetWorld()->GetFirstPlayerController());
	if(LoadingPlayerControler == nullptr) {
		return;
	}
	
	LoadingPlayerControler->ShowWidgets();
	
	// go to loading map
	UMobileDiabloMapCacheSubsystem* MapCacheSubsystem = this->GetGameInstance()->GetSubsystem<UMobileDiabloMapCacheSubsystem>();
	if (MapCacheSubsystem == nullptr) {
		return;	
	}

	FName CurrentMapName = MapCacheSubsystem->CurrentMapID;
	FName ToMapName = MapCacheSubsystem->ToMapID;
	MapCacheSubsystem->bAssetLoaded = false;

	if(ToMapName.IsNone()) {
		return;
	}
	
	
	UE_LOG(LogTemp, Log, TEXT("FROM %s TO %s"), *CurrentMapName.ToString(), *ToMapName.ToString());
	
	MapCacheSubsystem->UnloadMapResources(FString::Printf(TEXT("DataTable'/Game/DataTables/DT_%s.DT_%s'"), *CurrentMapName.ToString(), *CurrentMapName.ToString()), CurrentMapName);
	MapCacheSubsystem->OnAssetLoaded.BindUObject(this, &AMobileDiabloLoadingGameMode::ShowProgress);
	MapCacheSubsystem->LoadingMapResources(FString::Printf(TEXT("DataTable'/Game/DataTables/DT_%s.DT_%s'"), *ToMapName.ToString(), *ToMapName.ToString()), ToMapName);
	
}

void AMobileDiabloLoadingGameMode::ShowProgress(float TotalNum , float CurrentNum) {
	// 通知UI展现进度
	ShowProgressDelegate.Broadcast(TotalNum, CurrentNum);
}

void AMobileDiabloLoadingGameMode::GotoNextLevel() {
	const UMobileDiabloMapCacheSubsystem* MapCacheSubsystem = this->GetGameInstance()->GetSubsystem<UMobileDiabloMapCacheSubsystem>();
	if (MapCacheSubsystem == nullptr) {
		return;	
	}

	if(MapCacheSubsystem->ToMapID.IsNone()) {
		return;
	}
	
	UGameplayStatics::OpenLevel(this->GetWorld(), MapCacheSubsystem->ToMapID);
}

