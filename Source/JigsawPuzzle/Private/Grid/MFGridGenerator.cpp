// Fill out your copyright notice in the Description page of Project Settings.


#include "JigsawPuzzle/Public/Grid/MFGridGenerator.h"


AMFGridGenerator::AMFGridGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

	GridWidth = 5;
	GridHeight = 5;
	GridCellSize = 100;

}


void AMFGridGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	GridOrigin = GetActorLocation();
	GenerateGrid();
	
}

void AMFGridGenerator::GenerateGrid()
{
		for (int32 x = 0; x < GridWidth; x++)
		{
			for (int32 y = 0; y < GridHeight; y++)
			{
				FVector CellLocation = GridOrigin + FVector(x * GridCellSize, y * GridCellSize, 0);
				DrawDebugSphere(GetWorld(),CellLocation,10,12,FColor::Red, true, -1);
				
				FGridCell NewCell;
				NewCell.Location = CellLocation;
				NewCell.bOccupied = false;
				NewCell.OccupyingActor = nullptr;
				
				GridCells.Add(FIntPoint(x, y), NewCell);
			}
		}
}


FIntPoint AMFGridGenerator::GetNearestGridCoordFromLocation(FVector Location)
{
	int32 GridX = FMath::RoundToInt((Location.X - GridOrigin.X) / GridCellSize);
	int32 GridY = FMath::RoundToInt((Location.Y - GridOrigin.Y) / GridCellSize);
	
	return FIntPoint(GridX, GridY);
}

