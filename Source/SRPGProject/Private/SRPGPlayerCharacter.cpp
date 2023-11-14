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
}

void ASRPGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	HitDebugComponent->InitComponent(WeaponMeshComponent);
	HitDebugComponent->StartHitDebug(true);
}

void ASRPGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ASRPGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ASRPGPlayerCharacter::GetAttackRange()
{
	return AttackRange;
}