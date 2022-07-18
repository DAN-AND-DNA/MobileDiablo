#pragma once

#include "CoreMinimal.h"
#include "MobileDiablo/MobileDiabloGameModeBase.h"
#include "MobileDiabloStartGameMode.generated.h"

UCLASS(Blueprintable)
class MOBILEDIABLO_API  AMobileDiabloStartGameMode : public AMobileDiabloGameModeBase {
	GENERATED_BODY()
public:
	AMobileDiabloStartGameMode();

protected:
	virtual void BeginPlay() override;
};
