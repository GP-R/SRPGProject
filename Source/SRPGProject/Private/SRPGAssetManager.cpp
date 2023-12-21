// Fill out your copyright notice in the Description page of Project Settings.


#include "SRPGAssetManager.h"
#include "AbilitySystemGlobals.h"

const FPrimaryAssetType	USRPGAssetManager::UseItemType = TEXT("Use");
const FPrimaryAssetType	USRPGAssetManager::EquipmentItemType = TEXT("Equipment");
const FPrimaryAssetType	USRPGAssetManager::EtcItemType = TEXT("Etc");

void USRPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Log, TEXT("Hello World"));
}