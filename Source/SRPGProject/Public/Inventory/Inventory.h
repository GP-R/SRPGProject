// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/ItemPDA.h"
#include "Item/ItemSlotWidget.h"
#include "Inventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChanged, bool, bAdded, UItemPDA*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChangedNative, bool, UItemPDA*);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChanged, FItemSlot, ItemSlot, UItemPDA*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChangedNative, FItemSlot, UItemPDA*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SRPGPROJECT_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventory();

	UFUNCTION(BlueprintCallable)
	class UInventoryWidget* GetInventoryWidget() { return InventoryWidget; }

protected:
	virtual void BeginPlay() override;

	void NotifyInventoryItemChanged(bool bAdded, UItemPDA* Item);
	void NotifySlottedItemChanged(FItemSlot ItemSlot, UItemPDA* Item);

	bool FillEmptySlotWithItem(UItemPDA* NewItem);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ShowInventoryWidget();

	UFUNCTION(BlueprintCallable)
	bool AddInventoryItem(UItemPDA* NewItem, int32 ItemCount = 1, bool bAutoSlot = true);

	UFUNCTION(BlueprintPure)
	bool GetInventoryItemData(UItemPDA* Item, FItemData& ItemData) const;

	UFUNCTION(BlueprintImplementableEvent)
	void InventoryItemChanged(bool bAdded, UItemPDA* Item);

	UFUNCTION(BlueprintImplementableEvent)
	void SlottedItemChanged(FItemSlot ItemSlot, UItemPDA* Item);

	UFUNCTION(BlueprintCallable)
	bool SetSlottedItem(FItemSlot ItemSlot, UItemPDA* Item);

	UFUNCTION(BlueprintPure)
	UItemPDA* GetSlottedItem(FItemSlot ItemSlot) const;

	UFUNCTION(BlueprintPure)
	int32 GetInventoryItemCount(UItemPDA* Item) const;

	UFUNCTION(BlueprintCallable)
	bool RemoveInventoryItem(UItemPDA* RemovedItem, int32 RemoveCount = 1);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UItemPDA*, FItemData> InventoryData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FItemSlot, UItemPDA*> SlottedItems;

	UPROPERTY(BlueprintAssignable)
	FOnInventoryItemChanged OnInventoryItemChanged;

	FOnInventoryItemChangedNative OnInventoryItemChangedNative;

	UPROPERTY(BlueprintAssignable)
	FOnSlottedItemChanged OnSlottedItemChanged;

	FOnSlottedItemChangedNative OnSlottedItemChangedNative;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

private:
	UPROPERTY(VisibleAnywhere)
	class UInventoryWidget* InventoryWidget;

	UPROPERTY(VisibleAnywhere)
	bool bOnInventory;


};

