// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dialogue/DialogueData.h"
#include "Dialogue/DialogueWidget.h"
#include "DialogueController.generated.h"

/**
 * 
 */
UCLASS()
class SRPGPROJECT_API UDialogueController : public UObject
{
	GENERATED_BODY()
public:
	UDialogueController();

public:
	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void PlayDialogue(TArray<FDialogueData> DialogueDatas, bool bMovable);

	UFUNCTION()
	void PrintDialogue();

	void MovablePlayer(bool bMovable);

private:
	UPROPERTY()
	UDialogueWidget* DialogueWidget;

	TSubclassOf<UDialogueWidget> DialogueWidgetBP;

	TQueue<FDialogueData> DialogueDataQueue;

	class UAudioComponent* PlayerAudioComp;
};
