// Fill out your copyright notice in the Description page of Project Settings.


#include "MFGameModeMain.h"

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
