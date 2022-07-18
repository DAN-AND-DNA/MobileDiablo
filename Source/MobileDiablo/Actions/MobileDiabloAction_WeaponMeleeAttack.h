// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MobileDiabloAction.h"
#include "MobileDiabloAction_WeaponMeleeAttack.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MOBILEDIABLO_API UMobileDiabloAction_WeaponMeleeAttack : public UMobileDiabloAction {
	GENERATED_BODY()

public:
	// 两种思路
	// 1. 玩家装备武器时，对应的技能就添加到玩家的技能组件上，当玩家攻击时，启动武器技能，播放动画，启动武器的碰撞，如果碰撞到了就damage，记录本轮攻击的actor来去重，等动画结束了，就关闭武器碰撞
	UMobileDiabloAction_WeaponMeleeAttack();

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackAnimMontage;

	UPROPERTY(EditAnywhere)
	float AttackDistance;
	
	virtual bool StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float AtionKeepTime;

protected:
	FTimerHandle AttackTimerHandle;

	float MaxWalkSpeed;
	void RealMeleeAttack(class AMobileDiabloCharacter* InstigatorCharacter);
};

