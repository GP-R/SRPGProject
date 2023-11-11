// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SRPGProject.h"
#include "SRPGGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class SRPGPROJECT_API USRPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	USRPGGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	ESRPGAbilityInputID AbilityInputID = ESRPGAbilityInputID::None;
};
