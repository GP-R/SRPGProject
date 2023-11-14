// Fill out your copyright notice in the Description page of Project Settings.


#include "ComplexHitDebugComponent.h"

// Sets default values for this component's properties
UComplexHitDebugComponent::UComplexHitDebugComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UComplexHitDebugComponent::InitComponent()
{
	
}

void UComplexHitDebugComponent::StartHitDebug(bool bStart)
{

}

// Called when the game starts
void UComplexHitDebugComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UComplexHitDebugComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

