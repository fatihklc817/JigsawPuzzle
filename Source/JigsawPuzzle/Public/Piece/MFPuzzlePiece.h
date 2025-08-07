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
	UPROPERTY()
	class UMFPuzzleButtonWidget* PieceButtonWidget;
	
	
public:	
	AMFPuzzlePiece();

	UMFPuzzleButtonWidget* GetPieceButtonWidget();
	void SetPieceButtonWidget(UMFPuzzleButtonWidget* InPieceButtonWidget);

};
