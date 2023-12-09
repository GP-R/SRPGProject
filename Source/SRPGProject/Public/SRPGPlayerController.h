// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "SRPGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SRPGPROJECT_API ASRPGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASRPGPlayerController();

	UFUNCTION(BlueprintCallable)
	bool GetCanAttacking();

	UFUNCTION(BlueprintCallable)
	class ASRPGEnemyCharacter* GetTargetCharacter();

	UFUNCTION(BlueprintCallable)
	class UAudioComponent* GetAudioComponent() { return AudioComponent; }

	UFUNCTION(BlueprintCallable)
	class UDialogueController* GetDialogueController() { return DialogueController; }

	UFUNCTION(BlueprintCallable)
	void NextDialogue();

protected:
	uint32 bMoveToMouseCursor : 1;

	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void MoveToMouseCursor();

	void MoveToTouchLocation();

	void SetNewMoveDestination(const FVector DestLocation);

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

private:
	class ASRPGEnemyCharacter* Target;
	UPROPERTY(EditAnywhere)
	bool bCanAttacking;

	FGameplayTagContainer LocalAbilityTags;

	UPROPERTY(VisibleAnywhere)
	class UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere)
	class UDialogueController* DialogueController;

};
