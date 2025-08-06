// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/MFHudWidget.h"

#include "MFGameModeMain.h"
#include "Algo/RandomShuffle.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Ui/MFPuzzleButtonWidget.h"

void UMFHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMFGameModeMain* GameMode = Cast<AMFGameModeMain>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		 TArray<UPuzzlePieceData*> Pieces = GameMode->GetPuzzlePieces();
		
		Algo::RandomShuffle(Pieces);

		for (UPuzzlePieceData* Piece : Pieces)
		{
			UMFPuzzleButtonWidget* ButtonWidget = CreateWidget<UMFPuzzleButtonWidget>(this,PuzzleButtonWidgetClass);
			if (ButtonWidget)
			{
				ButtonWidget->SetPuzzlePieceData(Piece);
				ButtonWidget->InitializeButtonWithData();
				
				PiecesHorizontalBox->AddChildToHorizontalBox(ButtonWidget);
			}
		}

		
	
		
		
	}
	
}
