// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComplexHitDebugComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFirstHit, FHitResult, HitResult);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SRPGPROJECT_API UComplexHitDebugComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UComplexHitDebugComponent();

	void InitComponent(UPrimitiveComponent* WeaponComponent);

	UFUNCTION(BlueprintCallable)
	void StartHitDebug(bool bStart);

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:	
	UFUNCTION()
	void UpdatePrevSocketLocation();

	UFUNCTION()
	void FirstHitCheck(TArray<FHitResult> HitArray);

	UFUNCTION()
	void HitDebug();

public:
	UPROPERTY()
	class UPrimitiveComponent* Weapon;

	UPROPERTY()
	FOnFirstHit OnFirstHit;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> TraceIgnoreActors;

	UPROPERTY()
	bool bHitDebugging = false;

private:
	UPROPERTY()
	TArray<FName> WeaponSockets;

	UPROPERTY()
	TMap<FName, FVector> PrevSocketLocation;

	UPROPERTY()
	TArray<FHitResult> HitActors;

};
