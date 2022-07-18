// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloCharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/MobileDiabloActionComponent.h"
#include "Components/MobileDiabloInteractionComponent.h"
#include "MobileDiablo/Items/MobileDiabloEquipment.h"
#include "MobileDiablo/Items/MobileDiabloWeapon.h"
#include "EzAttributes/Public/EzAttributesComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ShowEquipment/Public/ShowEquipmentComponent.h"


AMobileDiabloCharacter::AMobileDiabloCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	// 技能组件
	this->ActionComp = CreateDefaultSubobject<UMobileDiabloActionComponent>("ActionComp");
	
	// 和外界进行互动的组件
	this->InteractionComp = CreateDefaultSubobject<UMobileDiabloInteractionComponent>(TEXT("InteractionComp"));
	
	// 创建阴影
	this->ShadownComp = CreateDefaultSubobject<UDecalComponent>(TEXT("ShadowComp"));
	this->ShadownComp->SetRelativeLocation(FVector(0.f,0.f,-170.f));
	this->ShadownComp->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	this->ShadownComp->DecalSize = FVector(160.f,64.f,64.f);
	
	// 创建属性组件
	this->AttributesComp = CreateDefaultSubobject<UEzAttributesComponent>(TEXT("AttributesComp"));
	this->AttributesComp->PrimaryComponentTick.bCanEverTick = false;
	
	// 创建装备展示组件
	this->ShowEquipmentComp = CreateDefaultSubobject<UShowEquipmentComponent>(TEXT("ShowEquipmentComp"));
	this->ShowEquipmentComp->PrimaryComponentTick.bCanEverTick = false;

	// 弹簧臂组件
	this->SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	this->SpringArmComp->SetupAttachment(this->RootComponent);
	this->SpringArmComp->TargetArmLength = 1200.f;
	this->SpringArmComp->bDoCollisionTest = false;
	this->SpringArmComp->bInheritYaw = false;
	this->SpringArmComp->SetRelativeRotation(FRotator(-50.f,0.f,0.f));
	
	// 摄像头组件
	this->CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	this->CameraComp->SetupAttachment(this->SpringArmComp);

	// 加速度为0时即开始制动
	UCharacterMovementComponent* CharacterMovementComp = this->GetCharacterMovement();
	CharacterMovementComp->bOrientRotationToMovement = true;
	CharacterMovementComp->GravityScale  = 50.f;
	CharacterMovementComp->BrakingFriction = 10.f;
	CharacterMovementComp->MaxAcceleration = 6000.f;
	CharacterMovementComp->GroundFriction = 400.f;
	CharacterMovementComp->BrakingDecelerationWalking = 4096.f;
	CharacterMovementComp->bRequestedMoveUseAcceleration = false;
	CharacterMovementComp->RotationRate = FRotator(0.f,850.f,0.f);

	// 第三人称
	this->bUseControllerRotationYaw = false;
}

void AMobileDiabloCharacter::PostInitializeComponents() {
	Super::PostInitializeComponents();
	
	// 注册属性
	this->AttributesComp->Register(FString(TEXT("Health")), 40, 40);
	this->AttributesComp->Register(FString(TEXT("Mana")), 30, 30);
	this->AttributesComp->Register(FString(TEXT("Energy")), 50, 50);
}

void AMobileDiabloCharacter::BeginPlay() {
	Super::BeginPlay();
	// 上层spawn时直接调用BeginPlay()
}

void AMobileDiabloCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMobileDiabloCharacter::Equip(AMobileDiabloEquipment* Equipment) {
	if (!IsValid(Equipment) || Equipment->ItemType != EMobileDiabloItemType::EEquipment || Equipment->Position == EShowEquipmentPosition::ENone) {
		return;
	}
	
	Equipments.Add(Equipment->Position, Equipment);
	this->ShowEquipmentComp->ShowEquipment(Equipment->Position, Equipment->SkeletalMeshComp->SkeletalMesh, Equipment->SkeletalMeshComp->GetMaterial(0));
}

void AMobileDiabloCharacter::Equip(AMobileDiabloWeapon* InWeapon) {
	if(!IsValid(InWeapon) || InWeapon->ItemType != EMobileDiabloItemType::EWeapon || this->ActionComp == nullptr) {
		return;
	}

	this->CurrentWeapon = InWeapon;
	this->CurrentWeapon->AttachedTo(this,  "HandSocket_R");

	// 武器的技能，比如普通攻击
	this->ActionComp->AddAction(this, this->CurrentWeapon->ActionClass);
}

void AMobileDiabloCharacter::SetHighlight(bool bEnable, int32 DepthStencilValue) {
	this->ShowEquipmentComp->SetRenderCustomDepth(bEnable);
	this->ShowEquipmentComp->SetCustomDepthStencilValue(DepthStencilValue);
}

bool AMobileDiabloCharacter::IsAlive() const {
	FEzAttribute Attribute;
	if (this->GetHealth(Attribute)) {
		return Attribute.CurrentValue > 0.f;
	}

	return false;
}

bool AMobileDiabloCharacter::IsAttack() const {
	return this->bAttacking;
}

bool AMobileDiabloCharacter::GetHealth(FEzAttribute& OutAttribute) const {
	FEzAttribute Attribute;
	if (this->AttributesComp->Get(TEXT("Health"), Attribute)) {
		OutAttribute = Attribute;
		return true;
	}

	return false;
}

bool AMobileDiabloCharacter::GetMana(FEzAttribute& OutAttribute) const {
	FEzAttribute Attribute;
	if (this->AttributesComp->Get(TEXT("Mana"), Attribute)) {
		OutAttribute = Attribute;
		return true;
	}

	return false;
}

bool AMobileDiabloCharacter::GetEnergy(FEzAttribute& OutAttribute) const {
	FEzAttribute Attribute;
	if (this->AttributesComp->Get(TEXT("Energy"), Attribute)) {
		OutAttribute = Attribute;
		return true;
	}

	return false;
}


void AMobileDiabloCharacter::GetSpeed2D(float& OutSpeed2D, FVector2D &OutVelocity2D) const {
	OutVelocity2D = FVector2D(this->GetVelocity());
	OutSpeed2D =(OutVelocity2D).Size();
}

void AMobileDiabloCharacter::EnableWeapon() {
	if (this->CurrentWeapon == nullptr) {
		return;
	}

	this->ActionComp->StartActionByID(this, this->CurrentWeapon->ActionID);
}

void AMobileDiabloCharacter::DisableWeapon() {
	if (this->CurrentWeapon == nullptr) {
		return;
	}

	this->ActionComp->StopActionByID(this, this->CurrentWeapon->ActionID);
}

void AMobileDiabloCharacter::InteractWithItem() {
	if(this->InteractionComp != nullptr) {
		AActor* Target = this->InteractionComp->GetNearestTarget();
		
		if(IsValid(Target) && Target->Implements<UMobileDiabloInteractable>()) {
			IMobileDiabloInteractable::Execute_Interact(Target, this);
		}
	}
}

