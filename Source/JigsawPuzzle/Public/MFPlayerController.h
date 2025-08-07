// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MFPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JIGSAWPUZZLE_API AMFPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UPROPERTY()									//a reference to our game mode 
	class AMFGameModeMain* GameModeRef;
	
	
	UPROPERTY(EditDefaultsOnly)						//hud widget class to create Hud
	TSubclassOf<class UMFHudWidget> HudWidgetClass;

	UPROPERTY()										//hud reference 
	class UMFHudWidget* Hud;

	
	UPROPERTY()									// a reference to grid generator;
	class AMFGridGenerator* GridGenerator;

	
	UPROPERTY()									// var to store selected piece
	class AMFPuzzlePiece* SelectedPiece;

	
	float OriginalZ = 0.f;					// selected pieces original z location.
	float HoverOffset = 20.f;				// offset to give the selected piece when dragging.

	
	//input 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* ClickAction;

	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SetupInputComponent() override;
	
	UFUNCTION()
	void OnClickStarted();

	UFUNCTION()
	void OnClikEnded();

	//This checks if the piece is in the right coord and sets the Tmap (PieceControlMap) which is in the game mode 
	UFUNCTION()
	void SetIsThePieceInRightPositionInControlMap(FIntPoint InGridCoord,class UPuzzlePieceData* InPieceData);
	
public:
	void SetSelectedPiece(AMFPuzzlePiece* InSelectedPiece);
	
	
};

