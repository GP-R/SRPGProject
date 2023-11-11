// Fill out your copyright notice in the Description page of Project Settings.


#include "SRPGPlayerController.h"
#include "SRPGEnemyCharacter.h"
#include "SRPGPlayerCharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"
#include "GameplayTagsManager.h"

ASRPGPlayerController::ASRPGPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bCanAttacking = false;
}

void ASRPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FGameplayTag AttackAbilityTag = UGameplayTagsManager::Get().RequestGameplayTag(FName("Ability.Melee"));
	LocalAbilityTags.AddTag(AttackAbilityTag);
}

void ASRPGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}

	FHitResult TraceHitResult;
	GetHitResultUnderCursor(ECC_Pawn, false, TraceHitResult);
	AActor* HitActor = TraceHitResult.GetActor();
	if (HitActor && HitActor->IsA(ASRPGEnemyCharacter::StaticClass()))
	{
		CurrentMouseCursor = EMouseCursor::Crosshairs;
	}
	else
	{
		CurrentMouseCursor = EMouseCursor::Default;
	}
}

void ASRPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ASRPGPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ASRPGPlayerController::OnSetDestinationReleased);
	//InputComponent->BindAction("SetDestination", IE_Repeat, this, &ASRPGPlayerController::MoveToTouchLocation);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASRPGPlayerController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASRPGPlayerController::MoveToTouchLocation);
}

void ASRPGPlayerController::MoveToMouseCursor()
{
	if (Target != nullptr)
	{
		return;
	}
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Pawn, false, Hit);

	if (Hit.bBlockingHit)
	{
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ASRPGPlayerController::MoveToTouchLocation()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ASRPGPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ASRPGPlayerController::OnSetDestinationPressed()
{
	bMoveToMouseCursor = true;

	ASRPGPlayerCharacter* SRPGPlayer = Cast<ASRPGPlayerCharacter>(GetPawn());

	FHitResult TraceHitResult;
	GetHitResultUnderCursor(ECC_Pawn, false, TraceHitResult);
	AActor* HitActor = TraceHitResult.GetActor();
	if (HitActor && HitActor->IsA(ASRPGEnemyCharacter::StaticClass()))
	{
		Target = Cast<ASRPGEnemyCharacter>(HitActor);
		if (FVector::DistXY(Target->GetActorLocation(), SRPGPlayer->GetActorLocation()) <= SRPGPlayer->GetAttackRange())
		{
			bCanAttacking = true;
			SRPGPlayer->ActivateAbilitiesWithTags(LocalAbilityTags, true);
		}
		else
		{
			bCanAttacking = false;
			SetNewMoveDestination(Target->GetActorLocation());
		}
	}
	else 
	{
		Target = nullptr;
		bCanAttacking = false;
		MoveToTouchLocation();
	}

}

void ASRPGPlayerController::OnSetDestinationReleased()
{
	bMoveToMouseCursor = false;
}

bool ASRPGPlayerController::GetCanAttacking()
{
	return bCanAttacking;
}

ASRPGEnemyCharacter* ASRPGPlayerController::GetTargetCharacter()
{
	return Target;
}