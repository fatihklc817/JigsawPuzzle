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
	
	UPROPERTY()
	TArray<class UMFPuzzleButtonWidget*> PuzzleWidgetPool;    //for storing a reference to all of our ui puzzle buttons' widgets
	
	UPROPERTY(meta=(BindWidget))
	class UHorizontalBox* PiecesHorizontalBox;			//The container widget to add and show our button widgets 

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMFPuzzleButtonWidget> PuzzleButtonWidgetClass;	//widget Class to spawn button widgets 

protected:
	virtual void NativeConstruct() override;

public:

	//refresh the ui - which buttons are enabled to use - show available ones
	void RefreshPuzzleWidgets();
};
