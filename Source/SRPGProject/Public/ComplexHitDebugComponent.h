// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComplexHitDebugComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SRPGPROJECT_API UComplexHitDebugComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UComplexHitDebugComponent();

	void InitComponent();

	UFUNCTION(BlueprintCallable)
	void StartHitDebug(bool bStart);

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:	
	UFUNCTION()
	void UpdateLastSocketLocation();

	UFUNCTION()
	void FindWeaponSocket();

public:
	UPROPERTY()
	class UPrimitiveComponent* Weapon;

	UPROPERTY()
	TArray<FHitResult> HitArray;

private:
	UPROPERTY()
	TArray<FName> WeaponSockets;

	UPROPERTY()
	TMap<FName, FVector> LastSocketLocation;

	UPROPERTY()
	bool bAttacking = false;
};
