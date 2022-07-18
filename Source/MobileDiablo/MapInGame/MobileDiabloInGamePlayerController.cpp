// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDiabloInGamePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/Classes/GameFramework/PlayerInput.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MobileDiablo/MobileDiabloCharacter.h"
#include "MobileDiablo/MobileDiabloMapCacheSubsystem.h"
#include "MobileDiablo/Assets/MobileDiabloMiscAsset.h"

AMobileDiabloInGamePlayerController::AMobileDiabloInGamePlayerController() {
	PrimaryActorTick.bCanEverTick = true;
}

void AMobileDiabloInGamePlayerController::BeginPlay() {
	Super::BeginPlay();

	if (this->HUDInst) {
		this->HUDInst->RemoveFromParent();
	}
	
	if (HUDClass) {
		this->HUDInst =	Cast<UMobileDiabloUserWidget> (CreateWidget(this, HUDClass));
		if (this->HUDInst) {
			this->HUDInst->OwnerPC = this;
			this->HUDInst->AddToViewport();
		}
	}
}

void AMobileDiabloInGamePlayerController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);
	this->CachedHero = Cast<AMobileDiabloCharacter>(InPawn);
}

void AMobileDiabloInGamePlayerController::OnUnPossess() {
	Super::OnUnPossess();
	this->CachedHero = nullptr;
}

void AMobileDiabloInGamePlayerController::OnMouseDown() {
	this->bMouseDown = true;
	this->bIsWalking = true;

	float OldSpeed2D;
	FVector2D OldVelocity2D;
	
	this->CachedHero->GetSpeed2D(OldSpeed2D,OldVelocity2D);
	// stop nav
	FNavigationSystem::StopMovement(*this);

	// keep old speed
	const FVector NewVelocity(OldVelocity2D.X, OldVelocity2D.Y, 0.f);
	this->CachedHero->GetCharacterMovement()->Velocity = NewVelocity;

	// show click point
	if(!this->ShowMoveID.IsNone()) {
		UMobileDiabloMapCacheSubsystem* MapCacheSubsystem = this->GetGameInstance()->GetSubsystem<UMobileDiabloMapCacheSubsystem>();
		if (IsValid(MapCacheSubsystem)) {
			UMobileDiabloMiscAsset* MiscAsset = MapCacheSubsystem->GetMiscAsset(this->ShowMoveID);
			if(IsValid(MiscAsset) && MiscAsset->MiscType == EMobileDiabloMiscType::EShowMove && MiscAsset->MiscClass ) 	{
				FHitResult Result;
				if (this->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),false, Result)) {
					FTransform ClickPosition (Result.Location);
					FActorSpawnParameters Parameters;
					Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					this->GetWorld()->SpawnActor(MiscAsset->MiscClass, &ClickPosition , Parameters);
				}
			}
		}
	}
}

void AMobileDiabloInGamePlayerController::OnMouseUp() {
	this->bMouseDown = false;

	this->bIsWalking = false;
	if(this->CachedHero->bAttacking) {
		return;
	}
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, this->WalkDest);
}

void AMobileDiabloInGamePlayerController::InteractWithItem() {
	if (this->CachedHero == nullptr) {
		return;
	}

	this->CachedHero->InteractWithItem();
}

void AMobileDiabloInGamePlayerController::TestAction() {
	if (this->CachedHero == nullptr) {
		return;
	}

	this->CachedHero->EnableWeapon();
	//this->CachedHero->DisableWeapon();
}

void AMobileDiabloInGamePlayerController::SetWalkDest() {
	FHitResult Result;
	if (this->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),false, Result)) {
		this->WalkDest = Result.Location;
		this->bIsWalking = true;
	}
}

bool AMobileDiabloInGamePlayerController::DistanceToWalkDest(const AActor* Actor, float& Distance, FVector& Direction) const {
	if (!IsValid(Actor)) {
		return false;
	}

	// 从actor朝向点击点
	FVector FromActorToWalkDest = this->WalkDest - Actor->GetActorLocation();
	FromActorToWalkDest = FromActorToWalkDest *  FVector(1.f,1.f,0.f);
	FromActorToWalkDest.ToDirectionAndLength(Direction, Distance);
	
	return true;
}

void AMobileDiabloInGamePlayerController::MoveToWalkDest() {
	if(	!IsValid(this->CachedHero) || !bIsWalking ) {
		return;
	}

	if(this->CachedHero->bAttacking) {
		return;
	}
	
	float Distance;
	FVector Direction;
	if(DistanceToWalkDest(this->CachedHero,Distance,Direction)) {
		if(Distance <= 10.f) {
			bIsWalking = false;
			return;
		}

		if(this->bMouseDown) {
			// 按照鼠标按下去位置做速度变化
			this->CachedHero->AddMovementInput(Direction, 	Distance/100.f);
		} else {
			this->CachedHero->AddMovementInput(Direction, 1);
		}
	}
}

// Called every frame
void AMobileDiabloInGamePlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(this->bMouseDown) {
		this->SetWalkDest();
	}
	
	this->MoveToWalkDest();	
}

void AMobileDiabloInGamePlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	
	this->InputComponent->BindAction("SetDest", EInputEvent::IE_Pressed, this, &AMobileDiabloInGamePlayerController::OnMouseDown);
	this->InputComponent->BindAction("SetDest", EInputEvent::IE_Released, this, &AMobileDiabloInGamePlayerController::OnMouseUp);
	this->InputComponent->BindAction("Interact",EInputEvent::IE_Pressed, this, &AMobileDiabloInGamePlayerController::InteractWithItem);
	this->InputComponent->BindAction("TestAction",EInputEvent::IE_Pressed, this, &AMobileDiabloInGamePlayerController::TestAction);
}

