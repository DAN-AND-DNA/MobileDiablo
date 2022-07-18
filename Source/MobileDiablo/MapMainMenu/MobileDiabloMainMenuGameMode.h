#pragma once

#include "CoreMinimal.h"
#include "MobileDiablo/MobileDiabloGameModeBase.h"
#include "MobileDiabloMainMenuGameMode.generated.h"


UCLASS(Blueprintable)
class AMobileDiabloMainMenuGameMode : public AMobileDiabloGameModeBase {
	GENERATED_BODY()
public:
	AMobileDiabloMainMenuGameMode();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SpawnPointMiscID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> HeroIDs;
};
