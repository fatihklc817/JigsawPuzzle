// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/MFPuzzleButtonWidget.h"

#include "MFPlayerController.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Data/PuzzlePieceData.h"
#include "Kismet/GameplayStatics.h"
#include "Piece/MFPuzzlePiece.h"
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

	AMFPuzzlePiece* SpawnedPiece = GetWorld()->SpawnActor<AMFPuzzlePiece>(PuzzlePieceData->Piece3DClass, FVector(0.f,0.f,100.f),FRotator::ZeroRotator, SpawnParams);
	SpawnedPiece->SetPieceButtonWidget(this);
	bIsUsed = true;
	HudRef->RefreshPuzzleWidgets();

	AMFPlayerController* PlayerController = Cast<AMFPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	PlayerController->SetSelectedPiece(SpawnedPiece);
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

void UMFPuzzleButtonWidget::SetIsUsed(bool InIsUsed)
{
	bIsUsed = InIsUsed;
}
