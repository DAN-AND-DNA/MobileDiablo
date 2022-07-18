// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloMainMenuPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MobileDiablo/MobileDiabloCharacter.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"


AMobileDiabloMainMenuPlayerController::AMobileDiabloMainMenuPlayerController() {
	PrimaryActorTick.bCanEverTick = true;
}

void AMobileDiabloMainMenuPlayerController::BeginPlay(){
	Super::BeginPlay();

	// create main menu widget
	if(!this->MainMenuClass) {
		return;
	}

	this->MainMenuInst = CreateWidget(this, this->MainMenuClass);
	if(this->MainMenuInst == nullptr) {
		return;
	}

	this->MainMenuInst->AddToViewport(10);
	//FVector Location = this->RootComponent->GetComponentLocation();
	//UE_LOG(LogTemp,Log, TEXT("=========== %s"), *Location.ToString());
	
}

AActor* AMobileDiabloMainMenuPlayerController::GetClosestTarget(bool bDebugDraw, float Radius) {
	// 无dpi缩放的视口鼠标位置，意思是，就像在widget中的鼠标位置，即所谓的local widget位置
	FVector2D MouseWidgetPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(this->GetWorld());
	if (Radius < 0.f) {
		Radius = 0.f;
	}

	float MinDistance2D = -1.f;
	// === this->GetHitResultUnderCursorForObjects() ===

	// 获得鼠标的在视口的坐标
	if (this->Player == nullptr) {
		return nullptr;
	}
	
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer> (this->Player);
	if (LocalPlayer == nullptr || LocalPlayer->ViewportClient == nullptr) {
		return nullptr;
	}

	FVector2D MousePosition2D = FVector2D::ZeroVector;
	LocalPlayer->ViewportClient->GetMousePosition(MousePosition2D);
	
	// 转成场景坐标，和从屏幕出发到点击点的方向
	FVector WorldPosition = FVector::ZeroVector;
	FVector WorldDirection = FVector::ZeroVector;
	AActor*	ClosestTarget = nullptr;
	
	if (UGameplayStatics::DeprojectScreenToWorld(this, MousePosition2D, WorldPosition, WorldDirection)) {
		TArray<AActor*> ActorsToIgnore;
		TArray<FHitResult> HitResults;

		EDrawDebugTrace::Type DebugDraw = EDrawDebugTrace::Type::None;
		if (bDebugDraw) {
			DebugDraw = EDrawDebugTrace::ForDuration;
		}
		
		if (UKismetSystemLibrary::SphereTraceMulti(this->GetWorld(), WorldPosition, WorldPosition+ 4000*WorldDirection, Radius, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_GameTraceChannel1), false, ActorsToIgnore, DebugDraw, HitResults, true)) {
			for(const FHitResult& HitResult: HitResults) {
				if (!HitResult.Actor.IsValid()) {
					continue;
				}
				
				// 获得英雄在local widget的位置
				FVector2D HeroWidgetPosition = FVector2D::ZeroVector;
				UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(this, HitResult.Actor.Get()->GetActorLocation(), HeroWidgetPosition, false);

				// 计算屏幕上的距离
				MousePosition2D = UWidgetLayoutLibrary::GetMousePositionOnViewport(this->GetWorld());
				const float Distance2D = FVector2D::Distance(MousePosition2D, HeroWidgetPosition);
				if (MinDistance2D == -1.f)	{
					MinDistance2D = Distance2D;
					ClosestTarget =  HitResult.Actor.Get();
				}
				
				if (Distance2D < MinDistance2D) {
					MinDistance2D = Distance2D;
					ClosestTarget =  HitResult.Actor.Get();
				}
			}
		}
	}
	
	return ClosestTarget;
}
