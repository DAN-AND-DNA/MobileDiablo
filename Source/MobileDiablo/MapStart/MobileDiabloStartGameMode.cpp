#include "MobileDiabloStartGameMode.h"
#include "MobileDiablo/MobileDiabloMapCacheSubsystem.h"
#include "Kismet/GameplayStatics.h"



AMobileDiabloStartGameMode::AMobileDiabloStartGameMode() {
}

void AMobileDiabloStartGameMode::BeginPlay() {
	AMobileDiabloGameModeBase::BeginPlay();

	
	// 1. TODO check pak and update

	// 2. Set Map Cache Subsystem
	UMobileDiabloMapCacheSubsystem* MapCacheSubsystem = this->GetGameInstance()->GetSubsystem<UMobileDiabloMapCacheSubsystem>();
	if (MapCacheSubsystem == nullptr) {
		return;	
	}

	MapCacheSubsystem->SetLoadingMap("MAP_Loading");
	MapCacheSubsystem->GotoMap(this->GetWorld()->GetFName(), "MAP_MainMenu");
}
