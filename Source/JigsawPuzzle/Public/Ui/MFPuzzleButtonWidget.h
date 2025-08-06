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

public:
	UPROPERTY(meta=(BindWidget))
	class UButton* Button;

	UPROPERTY(meta=(BindWidget))
	class UImage* PieceThumbnail;

	UPROPERTY()
	class UPuzzlePieceData* PuzzlePieceData;

	void SetPuzzlePieceData(UPuzzlePieceData* InPuzzlePieceData);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonClick();

public:
	UFUNCTION()
	void InitializeButtonWithData();
};
