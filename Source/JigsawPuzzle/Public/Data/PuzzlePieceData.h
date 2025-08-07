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

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FName PieceName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Thumbnail;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AMFPuzzlePiece> Piece3DClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntPoint PieceCorrectCoord;

	
	
};
