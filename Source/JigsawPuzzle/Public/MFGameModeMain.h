// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MFGameModeMain.generated.h"

/**
 * 
 */
UCLASS()
class JIGSAWPUZZLE_API AMFGameModeMain : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<class UPuzzlePieceData*> PuzzlePieces;

	UPROPERTY()
	class AMFGridGenerator* GridGenerator;


//Getter Setters
public:
	void SetGridGenerator(AMFGridGenerator* InGridGenerator);
	AMFGridGenerator* GetGridGenerator();

	TArray<UPuzzlePieceData*> GetPuzzlePieces();
	
};
