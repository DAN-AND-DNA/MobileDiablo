// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloEquipment.h"


AMobileDiabloEquipment::AMobileDiabloEquipment(){
	PrimaryActorTick.bCanEverTick = true;
	this->ItemType = EMobileDiabloItemType::EEquipment;
}

