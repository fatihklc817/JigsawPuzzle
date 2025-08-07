// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MFPuzzleButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class JIGSAWPUZZLE_API UMFPuzzleButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool bIsUsed;  //this bool is stores if this widget's piece is used or not 


	//widget ui components
	UPROPERTY(meta=(BindWidget))
	class UButton* Button;

	UPROPERTY(meta=(BindWidget))
	class UImage* PieceThumbnail;
	//

	
	UPROPERTY()
	class UPuzzlePieceData* PuzzlePieceData;  //ref to piece's DataAsset

	UPROPERTY() 
	class UMFHudWidget* HudRef;  //ref to HudWidget
	

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonClick();

	
public:

	//to set up this widget when creating;
	UFUNCTION()
	void InitializeButtonWithData(UMFHudWidget* InHud);
	
	
#pragma region Getter/Setters

	bool GetIsUsed();
	void SetIsUsed(bool InIsUsed);
	
	void SetPuzzlePieceData(UPuzzlePieceData* InPuzzlePieceData);
	UPuzzlePieceData* GetPuzzlePieceData();

#pragma endregion 
	
};
