// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloMiscAsset.h"

#include "MobileDiablo/MobileDiabloDefine.h"

FPrimaryAssetId UMobileDiabloMiscAsset::GetPrimaryAssetId() const {
	return FPrimaryAssetId(FMobileDiabloDefine::MiscAssetType, this->GetFName());
}
