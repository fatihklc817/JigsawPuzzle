// Fill out your copyright notice in the Description page of Project Settings.


#include "MFGameModeMain.h"


void AMFGameModeMain::BeginPlay()
{
	Super::BeginPlay();

	for (auto PuzzlePieceData : PuzzlePieces)
	{
		PieceControlMap.Add(PuzzlePieceData, false);
	}
}

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

#pragma endregion