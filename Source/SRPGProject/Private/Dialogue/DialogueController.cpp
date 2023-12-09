#include "Dialogue/DialogueController.h"
#include "SRPGPlayerController.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

UDialogueController::UDialogueController()
{
	DialogueWidget = CreateDefaultSubobject<UDialogueWidget>(TEXT("PlayerWidget"));

	static ConstructorHelpers::FClassFinder<UDialogueWidget> FDialogueWidgetBP(TEXT("WidgetBlueprint'/Game/Blueprints/WidgetBP/WBP_Dialogue.WBP_Dialogue_C'"));
	if (FDialogueWidgetBP.Succeeded())
	{
		DialogueWidgetBP = FDialogueWidgetBP.Class;
	}
}

void UDialogueController::Init()
{
	if (DialogueWidgetBP != nullptr)
	{
		DialogueWidget = Cast<UDialogueWidget>(CreateWidget(GetWorld(), DialogueWidgetBP));
		if (DialogueWidget != nullptr)
		{
			DialogueWidget->AddToViewport();
			DialogueWidget->SetActiveDialogueUI(false);
		}
	}

	ASRPGPlayerController* PC = Cast<ASRPGPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PlayerAudioComp = PC->GetAudioComponent();
	}
}

void UDialogueController::PlayDialogue(TArray<FDialogueData> DialogueDatas, bool bMovable)
{
	for (FDialogueData DialogueData : DialogueDatas)
	{
		DialogueDataQueue.Enqueue(DialogueData);
	}

	DialogueWidget->SetActiveDialogueUI(true);

	MovablePlayer(bMovable);
	PrintDialogue();
}

void UDialogueController::PrintDialogue()
{
	if (DialogueDataQueue.IsEmpty() && !PlayerAudioComp->IsPlaying())
	{
		MovablePlayer(true);
		DialogueWidget->SetActiveDialogueUI(false);
		return;
	}
	if (PlayerAudioComp->IsPlaying())
	{
		PlayerAudioComp->Stop();
		DialogueWidget->EndTypingTextEffect();
		return;
	}

	FDialogueData Temp;
	DialogueDataQueue.Dequeue(Temp);
	if (Temp.Sound)
	{
		PlayerAudioComp->SetSound(Temp.Sound);
		PlayerAudioComp->Play();
		//DialogueWidget->PlayTextTypingEffect(Temp.Text, Temp.Sound->Duration);
		DialogueWidget->SetDialogueText(Temp.Text);
		return;
	}
	DialogueWidget->SetDialogueText(Temp.Text);
}

void UDialogueController::MovablePlayer(bool bMovable)
{
	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!bMovable)
	{
		MyPawn->DisableInput(PC);
	}
	else
	{
		MyPawn->EnableInput(PC);
	}
}