#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/SRPGAbilityType.h"
#include "SRPGTargetType.generated.h"

class ASRPGCharacterBase;
class AActor;
struct FGameplayEventData;

/**
 * 
 */
UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class SRPGPROJECT_API USRPGTargetType : public UObject
{
	GENERATED_BODY()
	
public:
	USRPGTargetType() {}

	UFUNCTION(BlueprintNativeEvent)
	void GetTargets(ASRPGCharacterBase* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;

};

UCLASS(NotBlueprintable)
class SRPGPROJECT_API USRPGTargetType_UseOwner : public USRPGTargetType
{
	GENERATED_BODY()

public:
	USRPGTargetType_UseOwner() {}

	virtual void GetTargets_Implementation(ASRPGCharacterBase* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};

UCLASS(NotBlueprintable)
class SRPGPROJECT_API USRPGTargetType_UseEventData : public USRPGTargetType
{
	GENERATED_BODY()

public:
	USRPGTargetType_UseEventData() {}

	virtual void GetTargets_Implementation(ASRPGCharacterBase* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};
