// Fill out your copyright notice in the Description page of Project Settings.


#include "SRPGAssetManager.h"
#include "AbilitySystemGlobals.h"

void USRPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Log, TEXT("Hello World"));
}