// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloAction_WeaponMeleeAttack.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "MobileDiablo/MobileDiabloCharacter.h"

UMobileDiabloAction_WeaponMeleeAttack::UMobileDiabloAction_WeaponMeleeAttack()
	: AtionKeepTime(1.f)
	, MaxWalkSpeed(0.f) {
}

bool UMobileDiabloAction_WeaponMeleeAttack::StartAction_Implementation(AActor* Instigator) {
	AMobileDiabloCharacter* InstigatorCharacter = Cast<AMobileDiabloCharacter>(Instigator); 
	if (!IsValid(InstigatorCharacter)) {
		return false;
	}

	this->MaxWalkSpeed = InstigatorCharacter->GetCharacterMovement()->MaxWalkSpeed;
	InstigatorCharacter->bAttacking = true;
	InstigatorCharacter->GetCharacterMovement()->MaxWalkSpeed = 0.f;
	this->GetWorld()->GetFirstPlayerController()->StopMovement();
	
	// 给owner 打上tag
	Super::StartAction_Implementation(Instigator);
	
	// 1. 播放动画
	if(this->AttackAnimMontage) {
		InstigatorCharacter->PlayAnimMontage(this->AttackAnimMontage);
	}

	// 2. 延迟一小段时间
	FTimerDelegate RealAttack = FTimerDelegate::CreateUObject(this, &UMobileDiabloAction_WeaponMeleeAttack::RealMeleeAttack, InstigatorCharacter);
	this->GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, RealAttack, this->AtionKeepTime, false);
	return true;
}

void UMobileDiabloAction_WeaponMeleeAttack::StopAction_Implementation(AActor* Instigator) {
	Super::StopAction_Implementation(Instigator);
	
	AMobileDiabloCharacter* InstigatorCharacter = Cast<AMobileDiabloCharacter>(Instigator); 
	if (!IsValid(InstigatorCharacter)) {
		return;
	}
	// 1。停止当前动画
	InstigatorCharacter->StopAnimMontage();

	// 2. 停止定时器
	this->GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}

void UMobileDiabloAction_WeaponMeleeAttack::RealMeleeAttack(AMobileDiabloCharacter* InstigatorCharacter) {
	if (!IsValid(InstigatorCharacter)) {
		return;
	}

	// TODO 3. 在角色的前面创建一个小box检测
	
	// TODO 4. 对单次检测到的对象，施加damage
	this->StopAction(InstigatorCharacter);
	InstigatorCharacter->bAttacking = false;
	InstigatorCharacter->GetCharacterMovement()->MaxWalkSpeed = this->MaxWalkSpeed;
}
