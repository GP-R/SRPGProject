// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SRPGCharacterBase.h"
#include "SRPGPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SRPGPROJECT_API ASRPGPlayerCharacter : public ASRPGCharacterBase
{
	GENERATED_BODY()
public:
	ASRPGPlayerCharacter();

	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	FORCEINLINE class USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }

	UFUNCTION()
	float GetAttackRange();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComponent;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	float AttackRange;
};
