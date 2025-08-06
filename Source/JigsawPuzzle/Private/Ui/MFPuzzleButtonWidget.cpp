// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/MFPuzzleButtonWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Data/PuzzlePieceData.h"

void UMFPuzzleButtonWidget::SetPuzzlePieceData(UPuzzlePieceData* InPuzzlePieceData)
{
	PuzzlePieceData = InPuzzlePieceData;
}

void UMFPuzzleButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button)
	{
		Button->OnClicked.AddUniqueDynamic(this,&UMFPuzzleButtonWidget::OnButtonClick);
	}
	
}

void UMFPuzzleButtonWidget::OnButtonClick()
{
	
}

void UMFPuzzleButtonWidget::InitializeButtonWithData()
{
	PieceThumbnail->SetBrushFromTexture(PuzzlePieceData->Thumbnail);
}
