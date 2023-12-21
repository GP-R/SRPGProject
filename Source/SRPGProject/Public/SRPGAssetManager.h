// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SRPGAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class SRPGPROJECT_API USRPGAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static const FPrimaryAssetType	UseItemType;
	static const FPrimaryAssetType	EquipmentItemType;
	static const FPrimaryAssetType	EtcItemType;

	virtual void StartInitialLoading() override;
};
