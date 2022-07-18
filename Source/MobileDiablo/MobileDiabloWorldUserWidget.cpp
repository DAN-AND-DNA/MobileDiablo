// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloWorldUserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"


void UMobileDiabloWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime){
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(!IsValid(this->ParentSizeBox)) {
		return;
	}
	
	APlayerController* OwningPlayer = this->GetOwningPlayer();
	if(!IsValid(OwningPlayer)) {
		return;
	}
	
	if (!IsValid(AttachedActor)) {
		this->RemoveFromParent();
		return;
	}

	FVector2D ScreenPosition; 
	if (UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(OwningPlayer, AttachedActor->GetActorLocation(), ScreenPosition, false)) {
		this->ParentSizeBox->SetRenderTranslation(ScreenPosition);
		this->ParentSizeBox->SetVisibility(ESlateVisibility::HitTestInvisible);
	} else {
		this->ParentSizeBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}
