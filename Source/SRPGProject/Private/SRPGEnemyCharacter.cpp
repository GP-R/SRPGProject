// Fill out your copyright notice in the Description page of Project Settings.


#include "SRPGEnemyCharacter.h"
#include "AI/SRPGAIController.h"

#include "Animation/AnimMontage.h"

ASRPGEnemyCharacter::ASRPGEnemyCharacter()
{
	AIControllerClass = ASRPGAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASRPGEnemyCharacter::Attack()
{
    if (AttackMontage)
    {
        PlayAnimMontage(AttackMontage);
    }
}