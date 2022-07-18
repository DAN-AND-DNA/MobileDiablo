// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowEquipmentComponent.h"
#include "GameFramework/Character.h"


UShowEquipmentComponent::UShowEquipmentComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

bool UShowEquipmentComponent::ShowEquipment (const EShowEquipmentPosition Position, USkeletalMesh* NewEquipment,  UMaterialInterface* MaterialsInterface) {
	if(!IsValid(this->GetOwner()) || NewEquipment == nullptr || Position == EShowEquipmentPosition::ENone) {
		return false;
	}
	
	USkeletalMeshComponent* BaseSkeletalMeshComponent = nullptr;

	// as character
	const ACharacter* AsCharacter = Cast<ACharacter> (this->GetOwner());
	if (AsCharacter != nullptr) {
		BaseSkeletalMeshComponent = AsCharacter->GetMesh();
	}

	// as actor
	if (BaseSkeletalMeshComponent == nullptr) {
		BaseSkeletalMeshComponent = Cast<USkeletalMeshComponent> (this->GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	}
	
	if (BaseSkeletalMeshComponent == nullptr) {
		return false;
	} 
	
	FString DebugDisplayName;
	
	switch (Position)
	{
	case EShowEquipmentPosition::EHead:
		{
			DebugDisplayName = FString(TEXT("Head"));
			break;
		}
	case EShowEquipmentPosition::EBody:
		{
			DebugDisplayName = FString(TEXT("Body"));
			BaseSkeletalMeshComponent->SetSkeletalMesh(NewEquipment);
			return true;
			//break;
		}
	case EShowEquipmentPosition::ELeftArm:
		{
			DebugDisplayName = FString(TEXT("LeftArm"));
			break;
		}
	case EShowEquipmentPosition::ELeftHand:
		{
			DebugDisplayName = FString(TEXT("LeftHand"));
			break;
		}
	case EShowEquipmentPosition::ELeftLeg:
		{
			DebugDisplayName = FString(TEXT("LeftLeg"));
			break;
		}
	case EShowEquipmentPosition::ELeftFeet:
		{
			DebugDisplayName = FString(TEXT("LeftFeet"));
			break;
		}
	default:
		return false;
	}

	// clean old equipment
	USkeletalMeshComponent** Equipment = this->CurrentEquipments.Find(Position);
	if(Equipment != nullptr) {
		this->CurrentEquipments.Remove(Position);

		if(IsValid(*Equipment)) {
			(*Equipment)->UnregisterComponent();
			(*Equipment)->DestroyComponent();
		}
	}

	// add new equipment
	USkeletalMeshComponent* NewSkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this->GetOwner(), *DebugDisplayName);
	if (NewSkeletalMeshComponent == nullptr) {
		return false;
	}

	NewSkeletalMeshComponent->RegisterComponent();
	const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	NewSkeletalMeshComponent->bUseAttachParentBound = true;
	
	if (!NewSkeletalMeshComponent->AttachToComponent(BaseSkeletalMeshComponent, Rules)) {
		NewSkeletalMeshComponent->UnregisterComponent();
		NewSkeletalMeshComponent->DestroyComponent();
		NewSkeletalMeshComponent = nullptr;
		return false;
	}

	NewSkeletalMeshComponent->SetSkeletalMesh(NewEquipment);
	NewSkeletalMeshComponent->SetMaterial(0, MaterialsInterface);
	NewSkeletalMeshComponent->SetMasterPoseComponent(BaseSkeletalMeshComponent);
	
	
	this->CurrentEquipments.Add(Position, NewSkeletalMeshComponent);
	return true;
}

void  UShowEquipmentComponent::HideEquipment (const EShowEquipmentPosition Position) {
	if (!IsValid(this->GetOwner()) || Position == EShowEquipmentPosition::ENone) {
		return;
	}

	
	USkeletalMeshComponent** CurrentEquipment = this->CurrentEquipments.Find(Position);
	if (CurrentEquipment != nullptr) {
		this->CurrentEquipments.Remove(Position);
		(*CurrentEquipment)->UnregisterComponent();
		(*CurrentEquipment)->DestroyComponent();
	}
}

bool UShowEquipmentComponent::ShowWeapon(const FName& WeaponSocket, UStaticMesh* NewWeapon) {
	if(!IsValid(this->GetOwner()) || WeaponSocket.IsNone() || NewWeapon == nullptr) {
		return false;
	}

	USkeletalMeshComponent* BaseSkeletalMeshComponent = nullptr;
	
	// as character
	const ACharacter* AsCharacter = Cast<ACharacter> (this->GetOwner());
	if (AsCharacter != nullptr) {
		BaseSkeletalMeshComponent = AsCharacter->GetMesh();
	}

	// as actor
	if (BaseSkeletalMeshComponent == nullptr) {
		BaseSkeletalMeshComponent = Cast<USkeletalMeshComponent> (this->GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	}
	
	if (BaseSkeletalMeshComponent == nullptr) {
		return false;
	} 

	// clean old weapon
	UStaticMeshComponent** OldWeaponComp = (this->CurrentWeapons.Find(WeaponSocket));
	if (OldWeaponComp != nullptr) {
		this->CurrentWeapons.Remove(WeaponSocket);
		(*OldWeaponComp)->UnregisterComponent();
		(*OldWeaponComp)->DestroyComponent();
	}

	const FString DebugDisplayName = FString::Printf(TEXT("Weapon_%s"), *WeaponSocket.ToString());
	UStaticMeshComponent* NewWeaponComp = NewObject<UStaticMeshComponent>(this->GetOwner(), *DebugDisplayName);
	if (NewWeaponComp == nullptr) {
		return false;
	}
	
	NewWeaponComp->RegisterComponent();
	const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	NewWeaponComp->bUseAttachParentBound = true;
	if (!NewWeaponComp->AttachToComponent(BaseSkeletalMeshComponent, Rules, WeaponSocket)) {
		NewWeaponComp->UnregisterComponent();
		NewWeaponComp->DestroyComponent();
		NewWeaponComp = nullptr;
		return false;
	}
	NewWeaponComp->SetStaticMesh(NewWeapon);

	this->CurrentWeapons.Add(WeaponSocket, NewWeaponComp);
	return true;
	
}

void UShowEquipmentComponent::HideWeapon(const FName& WeaponSocket) {
	if (!IsValid(this->GetOwner()) || WeaponSocket.IsNone()) {
		return;
	}
	
	UStaticMeshComponent** CurrentWeapon = this->CurrentWeapons.Find(WeaponSocket);
	if (CurrentWeapon != nullptr) {
		this->CurrentWeapons.Remove(WeaponSocket);
		(*CurrentWeapon)->UnregisterComponent();
		(*CurrentWeapon)->DestroyComponent();
	}
}

void UShowEquipmentComponent::SetRenderCustomDepth (bool bEnable) {
	for (const TPair<EShowEquipmentPosition, USkeletalMeshComponent*>& Pair :CurrentEquipments) {
		Pair.Value->SetRenderCustomDepth(bEnable);
	}
}

void UShowEquipmentComponent::SetCustomDepthStencilValue (int32 StencilValue) {
	for (const TPair<EShowEquipmentPosition, USkeletalMeshComponent*>& Pair :CurrentEquipments) {
		Pair.Value->SetCustomDepthStencilValue(StencilValue);
	}
}

