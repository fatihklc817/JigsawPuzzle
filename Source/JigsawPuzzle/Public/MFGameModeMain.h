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

protected:

	//for counting player's moves
	int32 MoveCount;
	
	UPROPERTY(EditDefaultsOnly) //for creating end widget 
	TSubclassOf<UUserWidget> EndWidgetClass;
	

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta=(AllowPrivateAccess="true"))		//ref to all pieces' data to store for checking win condition
	TArray<class UPuzzlePieceData*> PuzzlePieces;

	UPROPERTY()  //win condition map - it stores every piece and a bool that says is the piece in right coord
	TMap<UPuzzlePieceData*,bool> PieceControlMap;
			
	
	UPROPERTY()  //a reference to gridGenerator 
	class AMFGridGenerator* GridGenerator;

public:
	virtual void BeginPlay() override;
	
	//checks the map - if every piece is in right coord, player wins. 
	void CheckWinCondition();

	void IncreaseMoveCount();

	UFUNCTION(BlueprintCallable)
	int32 GetMoveCount();


#pragma region Getter/Setters
	
public:
	void SetGridGenerator(AMFGridGenerator* InGridGenerator);
	AMFGridGenerator* GetGridGenerator();

	TArray<UPuzzlePieceData*> GetPuzzlePieces();

	TMap<UPuzzlePieceData*,bool>& GetPieceControlMap();

#pragma endregion


};
