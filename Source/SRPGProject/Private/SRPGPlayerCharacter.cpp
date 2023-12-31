// Fill out your copyright notice in the Description page of Project Settings.


#include "SRPGPlayerCharacter.h"
#include "SRPGPlayerController.h"
#include "SRPGEnemyCharacter.h"
#include "ComplexHitDebugComponent.h"

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "GameplayTagsManager.h"

ASRPGPlayerCharacter::ASRPGPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = 800.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-50.f, 0.f, 0.f));
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	HitDebugComponent = CreateDefaultSubobject<UComplexHitDebugComponent>(TEXT("HitDebugComponent"));

	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponMeshComponent->SetupAttachment(GetMesh(), "hand_r");

	AttackRange = 200.0f;
	OnHitCreateEffect.BindUFunction(this, "CreateHitEffect");
	OnHitSendEventToActor.BindUFunction(this, "SendHitEventToActor");
}

void ASRPGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	HitDebugComponent->InitComponent(WeaponMeshComponent);
}

void ASRPGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ASRPGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASRPGPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	HitDebugComponent->OnFirstHit.Add(OnHitCreateEffect);
	HitDebugComponent->OnFirstHit.Add(OnHitSendEventToActor);
}

void ASRPGPlayerCharacter::UnPossessed()
{
	Super::UnPossessed();
	HitDebugComponent->OnFirstHit.Remove(OnHitCreateEffect);
	HitDebugComponent->OnFirstHit.Remove(OnHitSendEventToActor);
}

void ASRPGPlayerCharacter::CreateHitEffect(FHitResult HitResult)
{
	FVector ImpactLocation = HitResult.ImpactPoint;
	FRotator ImpactRotation = FRotationMatrix::MakeFromZ(HitResult.ImpactNormal).Rotator();

	if (HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, ImpactLocation, ImpactRotation);
	}
}

void ASRPGPlayerCharacter::SendHitEventToActor(FHitResult HitResult)
{
	ASRPGEnemyCharacter* EnemyData = Cast<ASRPGEnemyCharacter>(HitResult.GetActor());
	if (EnemyData)
	{
		FGameplayEventData EventData;
		EventData.Instigator = GetInstigator();
		EventData.Target = HitResult.GetActor();
		FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
		TargetData->HitResult = HitResult;
		EventData.TargetData.Add(TargetData);
		FGameplayTag HitTag = UGameplayTagsManager::Get().RequestGameplayTag(FName("Weapon.Hit"));

		GetAbilitySystemComponent()->HandleGameplayEvent(HitTag, &EventData);
	}
}

float ASRPGPlayerCharacter::GetAttackRange()
{
	return AttackRange;
}