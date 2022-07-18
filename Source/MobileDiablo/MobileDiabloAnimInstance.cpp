// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloAnimInstance.h"
#include "MobileDiabloCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UMobileDiabloAnimInstance::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	this->Owner = Cast<AMobileDiabloCharacter> (this->GetOwningActor());
	if(!IsValid(Owner)) {
		return;
	}
}

void UMobileDiabloAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValid(Owner)) {
		return;
	}
	
	this->bAlive = this->Owner->IsAlive();

	FEzAttribute Attribute;
	if(this->Owner->GetHealth(Attribute)) {
		this->Health = Attribute.CurrentValue;
	}
	
	FVector2D Velocity2D;
	this->Owner->GetSpeed2D(this->Speed2D, Velocity2D);
	
	this->bAccelerated = false;
	if (this->Owner->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f) {
		this->bAccelerated = true;
	}
}
