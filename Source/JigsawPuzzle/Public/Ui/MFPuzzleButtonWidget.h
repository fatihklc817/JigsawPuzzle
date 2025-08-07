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
	bool bIsUsed;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* Button;

	UPROPERTY(meta=(BindWidget))
	class UImage* PieceThumbnail;

	UPROPERTY()
	class UPuzzlePieceData* PuzzlePieceData;

	UPROPERTY()
	class UMFHudWidget* HudRef;
	

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonClick();

public:
	UFUNCTION()
	void InitializeButtonWithData(UMFHudWidget* InHud);

	bool GetIsUsed();
	void SetIsUsed(bool InIsUsed);
	

	void SetPuzzlePieceData(UPuzzlePieceData* InPuzzlePieceData);
	UPuzzlePieceData* GetPuzzlePieceData();
};
