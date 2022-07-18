// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloHeroAsset.h"
#include "MobileDiablo/MobileDiabloDefine.h"

FPrimaryAssetId UMobileDiabloHeroAsset::GetPrimaryAssetId() const{
	return	FPrimaryAssetId(FMobileDiabloDefine::HeroAssetType, this->GetFName());
}
