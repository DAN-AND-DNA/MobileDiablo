// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloInteractionComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "MobileDiablo/MobileDiabloCharacter.h"
#include "MobileDiablo/MobileDiabloItem.h"
#include "MobileDiablo/MobileDiabloWorldUserWidget.h"
#include "MobileDiablo/Interfaces/MobileDiabloInteractable.h"


UMobileDiabloInteractionComponent::UMobileDiabloInteractionComponent()
	: TraceChannel (ECollisionChannel::ECC_GameTraceChannel2)
	, NearestTarget(nullptr)
	, WorldUserWidgetInst(nullptr) {
	
	PrimaryComponentTick.bCanEverTick = true;
}


void UMobileDiabloInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 每帧都重新计算
	this->NearestTarget = nullptr;
	
	AActor* Owner = this->GetOwner();
	if (!IsValid(Owner)) {
		return;
	}
	
	// 从actor的位置进行半径检测trace可以交互的对象
	const FVector StartTracePosition = Owner->GetActorLocation();
	const TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> HitsResults;

	
	if (UKismetSystemLibrary::SphereTraceMulti(this->GetWorld(), StartTracePosition, StartTracePosition + FVector(0.f, 0.f, -100),
										 200.f,UEngineTypes::ConvertToTraceType(TraceChannel), false, ActorsToIgnore,
									           EDrawDebugTrace::None, HitsResults, true)) {

		float MiniDistance = -1.f;
		
		for (const FHitResult& HitResult: HitsResults) {
			if (HitResult.Actor.IsValid())	{
				AActor*	HitActor = HitResult.Actor.Get();
				
				// 是否可为交互对象
				if (HitActor->Implements<UMobileDiabloInteractable>())	{
					FVector2D StartTracePosition2D(StartTracePosition);
					FVector2D HitActorPosition2D(HitActor->GetActorLocation());

					const float TempDistance = FVector2D::Distance(StartTracePosition2D, HitActorPosition2D);
					if (TempDistance < MiniDistance || MiniDistance == -1.f) {
						MiniDistance = TempDistance;
						this->NearestTarget = HitActor;
					}
				}
			}
		}
	}

	// 跟owner最近的物品先弹出提示widget
	if(this->NearestTarget == nullptr && this->WorldUserWidgetInst && this->WorldUserWidgetInst->IsInViewport()) {
		this->WorldUserWidgetInst->RemoveFromParent();
	}
	
	if(this->NearestTarget && this->WorldUserWidgetClass) {
		if (this->WorldUserWidgetInst == nullptr) {
			this->WorldUserWidgetInst = Cast<UMobileDiabloWorldUserWidget> (CreateWidget(this->GetWorld(), this->WorldUserWidgetClass));	
		}
		this->WorldUserWidgetInst->AttachedTo(this->NearestTarget);
		if (this->WorldUserWidgetInst && !this->WorldUserWidgetInst->IsInViewport()) {
			this->WorldUserWidgetInst->AddToViewport();
		}
	}
}

