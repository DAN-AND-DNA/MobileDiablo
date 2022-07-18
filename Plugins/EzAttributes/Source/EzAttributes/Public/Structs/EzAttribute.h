// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EzAttribute.generated.h"


USTRUCT(BlueprintType)
struct FEzAttribute : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinValue;
};