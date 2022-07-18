// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/ShowEquipmentPosition.h"
#include "Structs/ShowEquipmentInfo.h"
#include "ShowEquipmentComponent.generated.h"


UCLASS(ClassGroup=(AfternoonTea), meta=(BlueprintSpawnableComponent, DisplayName = "Show Equipment"))
class SHOWEQUIPMENT_API UShowEquipmentComponent : public UActorComponent {
	GENERATED_BODY()
public:
	UShowEquipmentComponent();
	
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	bool ShowEquipment(const EShowEquipmentPosition Position, USkeletalMesh* NewEquipment,  UMaterialInterface* MaterialInterface);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void HideEquipment (const EShowEquipmentPosition Position);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool ShowWeapon(const FName& WeaponSocket, UStaticMesh* NewWeapon);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void HideWeapon(const FName& WeaponSocket);

	UFUNCTION(BlueprintCallable)
	void SetRenderCustomDepth(bool bEnable);

	UFUNCTION(BlueprintCallable)
	void SetCustomDepthStencilValue(int32 StencilValue);

protected:
	UPROPERTY()
	TMap<EShowEquipmentPosition, USkeletalMeshComponent*> CurrentEquipments;

	UPROPERTY()
	TMap<FName, UStaticMeshComponent*> CurrentWeapons;
	
};
