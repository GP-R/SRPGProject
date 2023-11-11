// Fill out your copyright notice in the Description page of Project Settings.


#include "SRPGCharacterBase.h"
#include "SRPGPlayerController.h"
#include "SRPGProject.h"

#include "Abilities/SRPGAbilitySystemComponent.h"
#include "Abilities/SRPGGameplayAbility.h"
#include "Abilities/SRPGAttributeSet.h"
#include <GameplayEffectTypes.h>
#include "..\Public\SRPGCharacterBase.h"
#include "GameplayTagsManager.h"

ASRPGCharacterBase::ASRPGCharacterBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<USRPGAbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<USRPGAttributeSet>("Attributes");
	bAbilitiesInitialized = false;
}

UAbilitySystemComponent* ASRPGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASRPGCharacterBase::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
		bAbilitiesInitialized = true;
	}
}

void ASRPGCharacterBase::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (TSubclassOf<USRPGGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		}
	}
}

void ASRPGCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAttributes();
	GiveAbilities();
}

void ASRPGCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAttributes();
	if (AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "ESRPGAbilityInputID", static_cast<int32>(ESRPGAbilityInputID::Confirm), static_cast<int32>(ESRPGAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void ASRPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASRPGCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASRPGCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "ESRPGAbilityInputID", static_cast<int32>(ESRPGAbilityInputID::Confirm), static_cast<int32>(ESRPGAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}


void ASRPGCharacterBase::HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, ASRPGCharacterBase* InstigatorPawn, AActor* DamageCauser)
{
	OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorPawn, DamageCauser);
}

void ASRPGCharacterBase::HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
	{
		OnHealthChanged(DeltaValue, EventTags);
	}
}

void ASRPGCharacterBase::HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	if (bAbilitiesInitialized)
	{
		OnManaChanged(DeltaValue, EventTags);
	}
}

float ASRPGCharacterBase::GetHealth() const
{
	return Attributes->GetHealth();
}

float ASRPGCharacterBase::GetMaxHealth() const
{
	return Attributes->GetMaxHealth();
}

float ASRPGCharacterBase::GetMana() const
{
	return Attributes->GetMana();
}

float ASRPGCharacterBase::GetMaxMana() const
{
	return Attributes->GetMaxMana();
}

bool ASRPGCharacterBase::ActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags, bool bAllowRemoteActivation)
{
	if (AbilitySystemComponent)
	{
		return AbilitySystemComponent->TryActivateAbilitiesByTag(AbilityTags, bAllowRemoteActivation);
	}
	//FGameplayTag AttackAbilityTag = UGameplayTagsManager::Get().RequestGameplayTag(FName("Ability.Melee"));
	//AbilitySystemComponent->GetActiveEffectsWithAllTags(AttackAbilityTag)
	return false;
}

