// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SRPGAbilitySystemComponent.h"

void USRPGAbilitySystemComponent::ReceiveDamage(USRPGAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}
