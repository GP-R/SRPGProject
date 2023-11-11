// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SRPGAbilitySystemComponent.h"
#include "SRPGCharacterBase.h"
#include "Abilities/SRPGGameplayAbility.h"
#include "AbilitySystemGlobals.h"

USRPGAbilitySystemComponent::USRPGAbilitySystemComponent() {}

void USRPGAbilitySystemComponent::ReceiveDamage(USRPGAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}

void USRPGAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<USRPGGameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

	// Iterate the list of all ability specs
	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		// Iterate all instances on this ability spec
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();

		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbilities.Add(Cast<USRPGGameplayAbility>(ActiveAbility));
		}
	}
}

int32 USRPGAbilitySystemComponent::GetDefaultAbilityLevel() const
{
	ASRPGCharacterBase* OwningCharacter = Cast<ASRPGCharacterBase>(GetOwnerActor());

	if (OwningCharacter)
	{
		//return OwningCharacter->GetCharacterLevel();
	}
	return 1;
}

USRPGAbilitySystemComponent* USRPGAbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent)
{
	return Cast<USRPGAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}
