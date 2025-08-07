// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/MFPuzzleButtonWidget.h"

#include "MFPlayerController.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Data/PuzzlePieceData.h"
#include "Kismet/GameplayStatics.h"
#include "Piece/MFPuzzlePiece.h"
#include "Ui/MFHudWidget.h"



void UMFPuzzleButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button)
	{
		//bind on click function
		Button->OnClicked.AddUniqueDynamic(this,&UMFPuzzleButtonWidget::OnButtonClick);
	}
	
}

//spawns the piece, hides the ui button and refreshs the ui, and set the selected piece for player controller
void UMFPuzzleButtonWidget::OnButtonClick()
{
	FActorSpawnParameters SpawnParams;

	AMFPuzzlePiece* SpawnedPiece = GetWorld()->SpawnActor<AMFPuzzlePiece>(PuzzlePieceData->Piece3DClass, FVector(0.f,0.f,100.f),FRotator::ZeroRotator, SpawnParams);
	SpawnedPiece->SetPieceButtonWidget(this);
	bIsUsed = true;
	HudRef->RefreshPuzzleWidgets();

	AMFPlayerController* PlayerController = Cast<AMFPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	PlayerController->SetSelectedPiece(SpawnedPiece);
	
}

//to set up this widget when creating;
void UMFPuzzleButtonWidget::InitializeButtonWithData(UMFHudWidget* InHud)
{
	PieceThumbnail->SetBrushFromTexture(PuzzlePieceData->Thumbnail);
	HudRef = InHud;
}


#pragma region Getter/Setters

bool UMFPuzzleButtonWidget::GetIsUsed()
{
	return bIsUsed;
}

void UMFPuzzleButtonWidget::SetIsUsed(bool InIsUsed)
{
	bIsUsed = InIsUsed;
}

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

#pragma endregion