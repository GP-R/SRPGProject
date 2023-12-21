// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "AI/SRPGAIController.h"
#include "SRPGEnemyCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Enemy = Cast<ASRPGEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy == nullptr)
		return EBTNodeResult::Failed;

	Enemy->Attack();
	bIsAttacking = true;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBTTask_Attack::AttackCheck, 1.f, true, 1.f);
	/*Enemy->OnAttackEnd.AddLambda([this]()
		{
			bIsAttacking = false;
		});*/

	return Result;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (bIsAttacking == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

void UBTTask_Attack::AttackCheck()
{
	bIsAttacking = false;
}