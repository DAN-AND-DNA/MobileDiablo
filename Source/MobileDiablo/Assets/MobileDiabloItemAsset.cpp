#include "MobileDiabloItemAsset.h"

#include "MobileDiablo/MobileDiabloDefine.h"

FPrimaryAssetId UMobileDiabloItemAsset::GetPrimaryAssetId() const {
	return FPrimaryAssetId(FMobileDiabloDefine::ItemAssetType, GetFName());
}
