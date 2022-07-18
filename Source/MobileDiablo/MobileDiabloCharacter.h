// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/ShowEquipmentPosition.h"
#include "GameFramework/Character.h"
#include "Structs/EzAttribute.h"
#include "MobileDiabloCharacter.generated.h"

UCLASS()
class MOBILEDIABLO_API AMobileDiabloCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMobileDiabloCharacter();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Equip(class AMobileDiabloEquipment* Equipment);

	void Equip(class AMobileDiabloWeapon* Weapon);

	void SetHighlight(bool bEnable, int32 DepthStencilValue);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName HeroID;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsAttack() const;

	UFUNCTION(BlueprintCallable)
	bool GetHealth(FEzAttribute& OutAttribute) const;

	UFUNCTION(BlueprintCallable)
	bool GetMana(FEzAttribute& OutAttribute) const;

	UFUNCTION(BlueprintCallable)
	bool GetEnergy(FEzAttribute& OutAttribute) const;

	void GetSpeed2D(float& OutSpeed2D, FVector2D &OutVelocity2D) const;

	UFUNCTION(BlueprintCallable)
	void EnableWeapon();

	UFUNCTION(BlueprintCallable)
	void DisableWeapon();

	void InteractWithItem();

	bool bAttacking;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMobileDiabloActionComponent* ActionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMobileDiabloInteractionComponent* InteractionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDecalComponent* ShadownComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UEzAttributesComponent* AttributesComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UShowEquipmentComponent* ShowEquipmentComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* CameraComp;
	
	UPROPERTY()
	TMap<EShowEquipmentPosition, AMobileDiabloEquipment*> Equipments;

	UPROPERTY()
	AMobileDiabloWeapon* CurrentWeapon;

	
};

