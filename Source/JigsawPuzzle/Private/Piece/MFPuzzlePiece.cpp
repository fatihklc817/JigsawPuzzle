// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece/MFPuzzlePiece.h"

#include "Components/BoxComponent.h"

AMFPuzzlePiece::AMFPuzzlePiece()
{
 	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;
	
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

UPuzzlePieceData* AMFPuzzlePiece::GetPuzzlePieceData()
{
	return PuzzlePieceData;
}

void AMFPuzzlePiece::SetCurrentLocationGridPoint(FIntPoint InCurrentLocationGridPoint)
{
	CurrentLocationGridPoint = InCurrentLocationGridPoint;
	bIsPlacedBefore = true;
}

FIntPoint AMFPuzzlePiece::GetCurrentLocationGridPoint()
{
	if (CurrentLocationGridPoint != FIntPoint::ZeroValue)
	{
		return CurrentLocationGridPoint;
	}
	return FIntPoint::ZeroValue;
}

UStaticMeshComponent* AMFPuzzlePiece::GetMesh()
{
	return StaticMeshComponent;	
}

bool AMFPuzzlePiece::GetBIsPlacedBefore()
{
	return bIsPlacedBefore;
}



