// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/MFHudWidget.h"

#include "MFGameModeMain.h"
#include "Algo/RandomShuffle.h"
#include "Components/HorizontalBox.h"
#include "Data/PuzzlePieceData.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Ui/MFPuzzleButtonWidget.h"

void UMFHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMFGameModeMain* GameMode = Cast<AMFGameModeMain>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		 TArray<UPuzzlePieceData*> Pieces = GameMode->GetPuzzlePieces();

		//shuffles the pieces so every time it's sorted randomly in the ui
		Algo::RandomShuffle(Pieces);

		//creates, initializes and adds to the widget pool. for all piece's widget buttons 
		for (UPuzzlePieceData* Piece : Pieces)
		{
			UMFPuzzleButtonWidget* ButtonWidget = CreateWidget<UMFPuzzleButtonWidget>(this,PuzzleButtonWidgetClass);
			if (ButtonWidget)
			{
				ButtonWidget->SetPuzzlePieceData(Piece);
				ButtonWidget->InitializeButtonWithData(this);
				PuzzleWidgetPool.Add(ButtonWidget);
				PiecesHorizontalBox->AddChildToHorizontalBox(ButtonWidget);
			}
		}
	}
	
}


//refresh the ui - which buttons are enabled to use - show available ones
void UMFHudWidget::RefreshPuzzleWidgets()
{
	for (UMFPuzzleButtonWidget* Widget : PuzzleWidgetPool)
	{
		if (!Widget->GetIsUsed())
		{
			Widget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			Widget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}