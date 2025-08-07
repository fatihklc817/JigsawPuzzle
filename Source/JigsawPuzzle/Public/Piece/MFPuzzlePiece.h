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
	bool bIsPlacedBefore = false;

	UPROPERTY(VisibleAnywhere,Category="Components")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere,Category="Components")
	class UBoxComponent* BoxCollision;
	
	UPROPERTY()
	class UMFPuzzleButtonWidget* PieceButtonWidget;

	UPROPERTY(EditDefaultsOnly)
	class UPuzzlePieceData* PuzzlePieceData;

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
