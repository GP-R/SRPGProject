// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "SRPGAssetManager.h"
#include "ItemPDA.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class SRPGPROJECT_API UItemPDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UItemPDA()
		: Price(0)
		, MaxCount(1)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateBrush ItemIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FPrimaryAssetType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxCount;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
