// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/MFPuzzleButtonWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Data/PuzzlePieceData.h"
#include "Ui/MFHudWidget.h"

void UMFPuzzleButtonWidget::SetPuzzlePieceData(UPuzzlePieceData* InPuzzlePieceData)
{
	PuzzlePieceData = InPuzzlePieceData;
}

UPuzzlePieceData* UMFPuzzleButtonWidget::GetPuzzlePieceData()
{
	if (PuzzlePieceData != nullptr)
	{
		return PuzzlePieceData;
	}
	return nullptr;
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
	FActorSpawnParameters SpawnParams;
	
	GetWorld()->SpawnActor<AActor>(PuzzlePieceData->Piece3DClass,FVector::ZeroVector,FRotator::ZeroRotator,SpawnParams);
	bIsUsed = true;
	HudRef->RefreshPuzzleWidgets();
	//spawnla 3d de
	//refresh ui 
}

void UMFPuzzleButtonWidget::InitializeButtonWithData(UMFHudWidget* InHud)
{
	PieceThumbnail->SetBrushFromTexture(PuzzlePieceData->Thumbnail);
	HudRef = InHud;
}

bool UMFPuzzleButtonWidget::GetIsUsed()
{
	return bIsUsed;
}
