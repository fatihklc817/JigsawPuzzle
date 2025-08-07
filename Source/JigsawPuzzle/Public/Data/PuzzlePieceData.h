// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PuzzlePieceData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class JIGSAWPUZZLE_API UPuzzlePieceData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	//puzzle piece Data Asset
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FName PieceName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) //thumbnail 
	UTexture2D* Thumbnail;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly) //puzzle piece's 3d class to spawn in the world
	TSubclassOf<class AMFPuzzlePiece> Piece3DClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) //The piece's correct grid coordinate to check if the piece in right place
	FIntPoint PieceCorrectCoord;

	
	
};
