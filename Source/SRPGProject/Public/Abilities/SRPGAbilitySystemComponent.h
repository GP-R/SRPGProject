// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SRPGAbilitySystemComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, USRPGAbilitySystemComponent*, SourceASCfloat, float, UnmitigatedDamage, float, MitigatedDamage);
/**
 * 
 */
UCLASS()
class SRPGPROJECT_API USRPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	FReceivedDamageDelegate ReceivedDamage;

	virtual void ReceiveDamage(USRPGAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage);

public:
	//void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<USRPGGameplayAbility*>& ActiveAbilities);

};