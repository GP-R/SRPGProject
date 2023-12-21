#include "Inventory/Inventory.h"
#include "Inventory/InventoryWidget.h"

#include "Blueprint/UserWidget.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = true;

	bOnInventory = false;
}

void UInventory::BeginPlay()
{
	Super::BeginPlay();

	if (InventoryWidgetClass != nullptr)
	{
		InventoryWidget = Cast<UInventoryWidget>(CreateWidget(GetWorld(), InventoryWidgetClass));
		if (InventoryWidget != nullptr)
		{
			InventoryWidget->AddToViewport();
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	for (int32 SlotNumber = 0; SlotNumber < 50; SlotNumber++)
	{
		SlottedItems.Add(FItemSlot(USRPGAssetManager::UseItemType, SlotNumber), nullptr);
	}
}

void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInventory::ShowInventoryWidget()
{
	if (InventoryWidget != nullptr)
	{
		if (InventoryWidget->GetVisibility() == ESlateVisibility::Hidden)
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
			return;
		}
		else
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		//InventoryWidget->GetIsVisible() ? InventoryWidget->SetVisibility(ESlateVisibility::Hidden) : InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
	/*if (bOnInventory)
	{
		if (InventoryWidget != nullptr)
		{
			InventoryWidget->CloseInventory();
			bOnInventory = false;
			return;
		}
	}

	if (!bOnInventory)
	{

	}*/
}

bool UInventory::AddInventoryItem(UItemPDA* NewItem, int32 ItemCount, bool bAutoSlot)
{
	bool bChanged = false;
	if (!NewItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
		return false;
	}

	if (ItemCount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
		return false;
	}

	FItemData OldData;
	GetInventoryItemData(NewItem, OldData);

	FItemData NewData = OldData;
	NewData.UpdateItemData(FItemData(ItemCount), NewItem->MaxCount);

	if (OldData != NewData)
	{
		InventoryData.Add(NewItem, NewData);
		NotifyInventoryItemChanged(true, NewItem);
		bChanged = true;
	}

	if (bAutoSlot)
	{
		bChanged |= FillEmptySlotWithItem(NewItem);
	}

	if (bChanged)
	{
		return true;
	}
	return false;
}

bool UInventory::RemoveInventoryItem(UItemPDA* RemovedItem, int32 RemoveCount)
{
	if (!RemovedItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
		return false;
	}

	FItemData NewData;
	GetInventoryItemData(RemovedItem, NewData);

	if (!NewData.IsValid())
	{
		return false;
	}

	if (RemoveCount <= 0)
	{
		NewData.ItemCount = 0;
	}
	else
	{
		NewData.ItemCount -= RemoveCount;
	}

	if (NewData.ItemCount > 0)
	{
		InventoryData.Add(RemovedItem, NewData);
	}
	else
	{
		InventoryData.Remove(RemovedItem);

		for (TPair<FItemSlot, UItemPDA*>& Pair : SlottedItems)
		{
			if (Pair.Value == RemovedItem)
			{
				Pair.Value = nullptr;
				NotifySlottedItemChanged(Pair.Key, Pair.Value);
			}
		}
	}

	NotifyInventoryItemChanged(false, RemovedItem);

	return true;
}

int32 UInventory::GetInventoryItemCount(UItemPDA* Item) const
{
	const FItemData* FoundItem = InventoryData.Find(Item);

	if (FoundItem)
	{
		return FoundItem->ItemCount;
	}
	return 0;
}

bool UInventory::GetInventoryItemData(UItemPDA* Item, FItemData& ItemData) const
{
	const FItemData* FoundItem = InventoryData.Find(Item);

	if (FoundItem)
	{
		ItemData = *FoundItem;
		return true;
	}
	ItemData = FItemData(0);
	return false;
}

void UInventory::NotifyInventoryItemChanged(bool bAdded, UItemPDA* Item)
{
	OnInventoryItemChangedNative.Broadcast(bAdded, Item);
	OnInventoryItemChanged.Broadcast(bAdded, Item);

	InventoryItemChanged(bAdded, Item);
}

void UInventory::NotifySlottedItemChanged(FItemSlot ItemSlot, UItemPDA* Item)
{
	OnSlottedItemChangedNative.Broadcast(ItemSlot, Item);
	OnSlottedItemChanged.Broadcast(ItemSlot, Item);

	SlottedItemChanged(ItemSlot, Item);
}

bool UInventory::FillEmptySlotWithItem(UItemPDA* NewItem)
{
	FPrimaryAssetType NewItemType = NewItem->GetPrimaryAssetId().PrimaryAssetType;
	FItemSlot EmptySlot;
	for (TPair<FItemSlot, UItemPDA*>& Pair : SlottedItems)
	{
		if (Pair.Key.ItemType == NewItemType)
		{
			if (Pair.Value == NewItem)
			{
				return false;
			}
			else if (Pair.Value == nullptr && (!EmptySlot.IsValid() || EmptySlot.SlotNumber > Pair.Key.SlotNumber))
			{
				EmptySlot = Pair.Key;
			}
		}
	}

	if (EmptySlot.IsValid())
	{
		SlottedItems[EmptySlot] = NewItem;
		NotifySlottedItemChanged(EmptySlot, NewItem);
		return true;
	}

	return false;
}

bool UInventory::SetSlottedItem(FItemSlot ItemSlot, UItemPDA* Item)
{
	bool bFound = false;
	for (TPair<FItemSlot, UItemPDA*>& Pair : SlottedItems)
	{
		if (Pair.Key == ItemSlot)
		{
			bFound = true;
			Pair.Value = Item;
			NotifySlottedItemChanged(Pair.Key, Pair.Value);
		}
		else if (Item != nullptr && Pair.Value == Item)
		{
			Pair.Value = nullptr;
			NotifySlottedItemChanged(Pair.Key, Pair.Value);
		}
	}

	if (bFound)
	{
		return true;
	}

	return false;
}

UItemPDA* UInventory::GetSlottedItem(FItemSlot ItemSlot) const
{
	UItemPDA* const* FoundItem = SlottedItems.Find(ItemSlot);

	if (FoundItem)
	{
		return *FoundItem;
	}
	return nullptr;
}