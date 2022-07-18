#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MobileDiabloMapData.generated.h"

USTRUCT(BlueprintType)
struct FMobileDiabloMapData: public FTableRowBase  {
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UPrimaryDataAsset> Asset;
};
