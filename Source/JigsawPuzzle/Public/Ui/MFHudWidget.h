// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MFHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class JIGSAWPUZZLE_API UMFHudWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox* PiecesHorizontalBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMFPuzzleButtonWidget> PuzzleButtonWidgetClass;

protected:
	virtual void NativeConstruct() override;

	
};
