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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMFHudWidget> HudWidgetClass;

	UPROPERTY()
	class UMFHudWidget* Hud;
	
	UPROPERTY()  // a reference to grid generator;
	class AMFGridGenerator* GridGenerator;
	
	UPROPERTY()
	class AMFPuzzlePiece* SelectedPiece;

	float OriginalZ = 0.f;	// selected pieces original z location.
	float HoverOffset = 20.f; // offset to give the selected piece when dragging.
	
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

public:
	void SetSelectedPiece(AMFPuzzlePiece* InSelectedPiece);
	
};

