// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemPDA.h"
#include "UseItem.generated.h"

/**
 * 
 */
UCLASS()
class SRPGPROJECT_API UUseItem : public UItemPDA
{
	GENERATED_BODY()
	
public:
	UUseItem()
	{
		ItemType = USRPGAssetManager::UseItemType;
	}
};
