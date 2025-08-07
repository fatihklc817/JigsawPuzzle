// Fill out your copyright notice in the Description page of Project Settings.


#include "MFGameModeMain.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


void AMFGameModeMain::BeginPlay()
{
	Super::BeginPlay();
	
	//initializes PieceControlMap - adds all pieces to TMap.
	for (auto PuzzlePieceData : PuzzlePieces)
	{
		PieceControlMap.Add(PuzzlePieceData, false);
	}

	
}

//checks the map - if every piece is in right coord, player wins. 
void AMFGameModeMain::CheckWinCondition()
{
	for (auto Piece : PieceControlMap)
	{
		if (Piece.Value == false)
		{
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("KAZANDINNNNNNN "));

	auto PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	auto EndWidget = CreateWidget(PlayerController,EndWidgetClass);
	if (EndWidget)
	{
		EndWidget->AddToViewport();
		FInputModeUIOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
	
}

void AMFGameModeMain::IncreaseMoveCount()
{
	MoveCount++;
}


#pragma region Getter/Setters

void AMFGameModeMain::SetGridGenerator(AMFGridGenerator* InGridGenerator)
{
	GridGenerator = InGridGenerator;
}

AMFGridGenerator* AMFGameModeMain::GetGridGenerator()
{
	return GridGenerator;
}

TArray<UPuzzlePieceData*> AMFGameModeMain::GetPuzzlePieces()
{
	return PuzzlePieces;
}

TMap<UPuzzlePieceData*, bool>& AMFGameModeMain::GetPieceControlMap()
{
	return PieceControlMap;
}

int32 AMFGameModeMain::GetMoveCount()
{
	return MoveCount;
}


#pragma endregion
