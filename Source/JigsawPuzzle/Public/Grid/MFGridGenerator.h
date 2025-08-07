// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MFGridGenerator.generated.h"

//grid cell struct 
USTRUCT(BlueprintType)
struct FGridCell
{
	GENERATED_BODY()

	FVector Location;	//location for snapping pieces 
	
	bool bOccupied = false;

	UPROPERTY()
	TObjectPtr<AActor> OccupyingActor; 
};


UCLASS()
class JIGSAWPUZZLE_API AMFGridGenerator : public AActor
{
	GENERATED_BODY()

protected:
	//parameters for creating a grid
	UPROPERTY(EditDefaultsOnly,Category="Grid")
	int32 GridWidth;

	UPROPERTY(EditDefaultsOnly,Category="Grid")
	int32 GridHeight;

	UPROPERTY(EditDefaultsOnly,Category="Grid")
	float GridCellSize;
	//
	
	TMap<FIntPoint, FGridCell> GridCells;		//this TMap is for pairing up the cells and its coordination in the grid 

	FVector GridOrigin;
	
public:	
	AMFGridGenerator();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void GenerateGrid();

public:
	UFUNCTION()		//find nearest grid point from given location
	FIntPoint GetNearestGridCoordFromLocation(FVector Location);

	// returns the closest gridcell in the given coord // TOptional is just for C++. if you want blueprint access, you can make IsValid control in the FGridCell struct
	FGridCell* GetGridCellAtGivenGridCoord(FIntPoint GridCoord);
	
	
};
