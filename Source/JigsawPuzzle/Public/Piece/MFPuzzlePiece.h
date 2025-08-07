// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MFPuzzlePiece.generated.h"

UCLASS()
class JIGSAWPUZZLE_API AMFPuzzlePiece : public AActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere)		
	bool bIsPlacedBefore = false;	//to Check whether the piece was created from the user interface or whether it already exists in the grid. // this is for swapping 		

	UPROPERTY(VisibleAnywhere,Category="Components")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY()
	class UMFPuzzleButtonWidget* PieceButtonWidget; //this is a reference to the ui button of the puzzle piece, so if we remove the piece from the grid, we can show the ui button again

	UPROPERTY(EditDefaultsOnly)
	class UPuzzlePieceData* PuzzlePieceData;  //reference to piece's data

	UPROPERTY()
	FIntPoint CurrentLocationGridPoint;  
	
public:	
	AMFPuzzlePiece();

#pragma region Getter/Setters
	
	UMFPuzzleButtonWidget* GetPieceButtonWidget();
	void SetPieceButtonWidget(UMFPuzzleButtonWidget* InPieceButtonWidget);

	UPuzzlePieceData* GetPuzzlePieceData();

	void SetCurrentLocationGridPoint(FIntPoint InCurrentLocationGridPoint);
	FIntPoint GetCurrentLocationGridPoint();

	UStaticMeshComponent* GetMesh();

	bool GetBIsPlacedBefore();
	
#pragma endregion 
};
