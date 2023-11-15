#include "ComplexHitDebugComponent.h"

#include "Kismet/KismetSystemLibrary.h"

UComplexHitDebugComponent::UComplexHitDebugComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UComplexHitDebugComponent::InitComponent(UPrimitiveComponent* WeaponComponent)
{
	this->Weapon = WeaponComponent;

	WeaponSockets = Weapon->GetAllSocketNames();
	bHitDebugging = false;
}

// 애님 노티파이 start와 end에서 호출
void UComplexHitDebugComponent::StartHitDebug(bool bStart)
{
	if (bStart)
	{
		PrevSocketLocation.Empty();
		UpdatePrevSocketLocation();
		HitActors.Empty();
	}
	bHitDebugging = bStart;
}

void UComplexHitDebugComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UComplexHitDebugComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bHitDebugging && Weapon)
	{
		HitDebug();
		UpdatePrevSocketLocation();
	}
}

void UComplexHitDebugComponent::UpdatePrevSocketLocation()
{
	for (FName SocketName : WeaponSockets)
	{
		PrevSocketLocation.Add(SocketName, Weapon->GetSocketLocation(SocketName));
	}
}

void UComplexHitDebugComponent::FirstHitCheck(TArray<FHitResult> HitArray)
{
	for (const FHitResult& Hit : HitArray)
	{
		bool bIsSameActor = HitActors.ContainsByPredicate([&](const FHitResult& HitActor) 
			{  
				return HitActor.Actor == Hit.Actor;
			});
		if (!bIsSameActor)
		{
			HitActors.Add(Hit);
			OnFirstHit.Broadcast(Hit);
			UE_LOG(LogTemp, Log, TEXT("Hit"));
		}
	}
	/*TArray<TWeakObjectPtr<AActor>> HitActors;
	for (const FHitResult& Hit : HitArray)
	{
		bool bIsSameActor = HitActors.ContainsByPredicate([&](const TWeakObjectPtr<AActor>& HitActor) 
			{  
				return HitActor == Hit.Actor;
			});
		if (!bIsSameActor)
		{
			HitActors.Add(Hit.Actor);
			OnFirstHit.Broadcast(Hit);
		}
	}*/
}

void UComplexHitDebugComponent::HitDebug()
{
	TArray<FHitResult> HitResults;
	UObject* curWorld = this;
	FVector Start;
	FVector End;

	for (FName WeaponSocket_1 : WeaponSockets)
	{
		for (FName WeaponSocket_2 : WeaponSockets)
		{
			Start = Weapon->GetSocketLocation(WeaponSocket_1);
			End = *(PrevSocketLocation.Find(WeaponSocket_2));

			UKismetSystemLibrary::LineTraceMulti(
				curWorld,
				Start,
				End,
				UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1),
				true,
				TraceIgnoreActors,
				EDrawDebugTrace::Type::ForDuration,
				HitResults,
				true,
				FLinearColor::Red,
				FLinearColor::Green,
				1.0f);

			FirstHitCheck(HitResults);
			HitResults.Empty();
		}

		for (FName WeaponSocket_3 : WeaponSockets)
		{
			Start = *(PrevSocketLocation.Find(WeaponSocket_3));
			End = Weapon->GetSocketLocation(WeaponSocket_1);

			UKismetSystemLibrary::LineTraceMulti(
				curWorld, 
				Start, 
				End, 
				UEngineTypes::ConvertToTraceType(ECC_Visibility),
				true,
				TraceIgnoreActors,
				EDrawDebugTrace::Type::ForDuration,
				HitResults,
				true,
				FLinearColor::Red,
				FLinearColor::Green,
				1.0f);

			FirstHitCheck(HitResults);
			HitResults.Empty();
		}
	}
}
