// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece/MFPuzzlePiece.h"

AMFPuzzlePiece::AMFPuzzlePiece()
{
 	PrimaryActorTick.bCanEverTick = false;

}

UMFPuzzleButtonWidget* AMFPuzzlePiece::GetPieceButtonWidget()
{
	if (PieceButtonWidget != nullptr)
	{
		return PieceButtonWidget;
	}
	
	return nullptr;
}

void AMFPuzzlePiece::SetPieceButtonWidget(UMFPuzzleButtonWidget* InPieceButtonWidget)
{
	PieceButtonWidget = InPieceButtonWidget;
}



