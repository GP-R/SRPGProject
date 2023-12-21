// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/PrimaryAssetId.h"
#include "ItemSlotWidget.generated.h"

USTRUCT(BlueprintType)
struct SRPGPROJECT_API FItemData
{
	GENERATED_BODY()

	FItemData()
		: ItemCount(1)
	{}

	FItemData(int32 InItemCount)
		: ItemCount(InItemCount)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemCount;

	bool operator==(const FItemData& Other) const
	{
		return ItemCount == Other.ItemCount;
	}
	bool operator!=(const FItemData& Other) const
	{
		return !(*this == Other);
	}

	bool IsValid() const
	{
		return ItemCount > 0;
	}

	void UpdateItemData(const FItemData& Other, int32 MaxCount)
	{
		if (MaxCount <= 0)
		{
			MaxCount = MAX_int32;
		}

		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount);
	}
};

USTRUCT(BlueprintType)
struct SRPGPROJECT_API FItemSlot
{
	GENERATED_BODY()

	FItemSlot()
		: SlotNumber(-1) 
	{}

	FItemSlot(const FPrimaryAssetType& InItemType, int32 InSlotNumber)
		: ItemType(InItemType)
		, SlotNumber(InSlotNumber)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPrimaryAssetType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotNumber;

	bool operator==(const FItemSlot& Other) const
	{
		return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber;
	}
	bool operator!=(const FItemSlot& Other) const
	{
		return !(*this == Other);
	}

	friend inline uint32 GetTypeHash(const FItemSlot& Key)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
		return Hash;
	}

	bool IsValid() const
	{
		return ItemType.IsValid() && SlotNumber >= 0;
	}
};

UCLASS()
class SRPGPROJECT_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemSlot ItemSlot;


};
