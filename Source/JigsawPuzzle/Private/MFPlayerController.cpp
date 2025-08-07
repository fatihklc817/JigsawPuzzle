// Fill out your copyright notice in the Description page of Project Settings.


#include "JigsawPuzzle/Public/MFPlayerController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MFGameModeMain.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Data/PuzzlePieceData.h"
#include "Grid/MFGridGenerator.h"
#include "Piece/MFPuzzlePiece.h"
#include "Ui/MFHudWidget.h"
#include "Ui/MFPuzzleButtonWidget.h"


void AMFPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Add mapping context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	bShowMouseCursor = true;

	//Find camera and Set view target for player
	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);

	if (FoundCameras.Num() > 0)
	{
		SetViewTarget(Cast<ACameraActor>(FoundCameras[0]));
	}

	if (HudWidgetClass)
	{
		Hud = CreateWidget<UMFHudWidget>(this, HudWidgetClass);
		Hud->AddToViewport();
	}

	GameModeRef = Cast<AMFGameModeMain>(UGameplayStatics::GetGameMode(GetWorld()));
	
	

}

void AMFPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (SelectedPiece)
	{
		FHitResult Hit;
	
		FVector WorldOrigin, WorldDirection;
		DeprojectMousePositionToWorld(WorldOrigin, WorldDirection);
	
		if (GetWorld()->LineTraceSingleByChannel(Hit, WorldOrigin, WorldOrigin + WorldDirection * 10000, ECC_Visibility))
		{
			//DrawDebugSphere(GetWorld(), Hit.Location, 10.0f, 10, FColor::Green, false, 2.f, 0, 1.0f);
			//DrawDebugLine(GetWorld(), WorldOrigin, Hit.Location, FColor::Green, false, 2.f, 0, 1.0f);
			
			FVector Location = Hit.ImpactPoint;
			FVector TargetLocation = FVector(Location.X, Location.Y, OriginalZ + HoverOffset);
			SelectedPiece->SetActorLocation(TargetLocation);
		}
	}

	
	
}

void AMFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started,this, &AMFPlayerController::OnClickStarted);
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Completed,this, &AMFPlayerController::OnClikEnded);
	}
}

void AMFPlayerController::OnClickStarted()
{
	if (SelectedPiece != nullptr)
	{
		OnClikEnded();
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Clicked"));
	
	FVector WorldOrigin, WorldDirection;
	DeprojectMousePositionToWorld(WorldOrigin,WorldDirection);
	
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, WorldOrigin, WorldOrigin + WorldDirection * 10000, ECC_Visibility))
	{
		//DrawDebugSphere(GetWorld(), Hit.Location, 10.0f, 10, FColor::Green, false, 10.f, 0, 1.0f);
		//DrawDebugLine(GetWorld(), WorldOrigin, Hit.Location, FColor::Green, false, 10.f, 0, 1.0f);
		if (Hit.GetActor() && Hit.GetActor()->ActorHasTag("piece"))
		{
			OriginalZ = Hit.GetActor()->GetActorLocation().Z;
			SelectedPiece = Cast<AMFPuzzlePiece>(Hit.GetActor());
			UE_LOG(LogTemp, Warning, TEXT("name : %s"),*SelectedPiece->GetActorNameOrLabel());
		}
	}

	

}

void AMFPlayerController::OnClikEnded()
{
	if (SelectedPiece == nullptr)
	{
		return;
	}

	if (GridGenerator == nullptr)
	{
		GridGenerator = Cast<AMFGameModeMain>(UGameplayStatics::GetGameMode(GetWorld()))->GetGridGenerator();
	}
	
	FVector PieceLocation = SelectedPiece->GetActorLocation();
	FIntPoint NearestGridCoord = GridGenerator->GetNearestGridCoordFromLocation(PieceLocation);
	UE_LOG(LogTemp, Warning, TEXT("grid point : %d %d"), NearestGridCoord.X, NearestGridCoord.Y);
	
	if (FGridCell* GridCell = GridGenerator->GetGridCellAtGivenGridCoord(NearestGridCoord))
	{

		

		if (GridCell->OccupyingActor)
		{
			auto OldOccupyingPiece = Cast<AMFPuzzlePiece>(GridCell->OccupyingActor);
			if (!SelectedPiece->GetBIsPlacedBefore()) //if the cell is occypied and the new piece is coming from hud 
			{
				OldOccupyingPiece->GetPieceButtonWidget()->SetIsUsed(false);
				Hud->RefreshPuzzleWidgets();
				OldOccupyingPiece->Destroy();
				
			}
			else                                      //the cell is occupied and the new piece is coming from another grid cell. so we switch 
			{
				if (FGridCell* NewPiecesGridCell = GridGenerator->GetGridCellAtGivenGridCoord(SelectedPiece->GetCurrentLocationGridPoint()))
				{
					OldOccupyingPiece->SetActorLocation(NewPiecesGridCell->Location);
					OldOccupyingPiece->SetCurrentLocationGridPoint(SelectedPiece->GetCurrentLocationGridPoint());
					NewPiecesGridCell->OccupyingActor = OldOccupyingPiece;

					SetIsThePieceInRightPositionInControlMap(SelectedPiece->GetCurrentLocationGridPoint(),OldOccupyingPiece->GetPuzzlePieceData());
				}
			}
		}
		
		
		
		SelectedPiece->SetActorLocation(FVector(GridCell->Location.X, GridCell->Location.Y, OriginalZ));
		SelectedPiece->SetCurrentLocationGridPoint(NearestGridCoord);

		GridCell->OccupyingActor = SelectedPiece;
		
		//check win condition
		SetIsThePieceInRightPositionInControlMap(NearestGridCoord, SelectedPiece->GetPuzzlePieceData());
		
		GameModeRef->CheckWinCondition();
		
		SelectedPiece = nullptr;
	}
	else
	{
		
		SelectedPiece->GetPieceButtonWidget()->SetIsUsed(false);
		Hud->RefreshPuzzleWidgets();
		SelectedPiece->Destroy();
		SelectedPiece = nullptr;
	}
	

}


void AMFPlayerController::SetSelectedPiece(AMFPuzzlePiece* InSelectedPiece)
{
	OriginalZ = InSelectedPiece->GetActorLocation().Z;
	SelectedPiece = InSelectedPiece;
	HoverOffset = 20;
}


void AMFPlayerController::SetIsThePieceInRightPositionInControlMap(FIntPoint InGridCoord, UPuzzlePieceData* InPieceData)
{
	TMap<UPuzzlePieceData*, bool>& PieceControlMap = GameModeRef->GetPieceControlMap();
	if (InGridCoord == InPieceData->PieceCorrectCoord)
	{
			
		PieceControlMap[InPieceData] = true;
	}
	else
	{
		PieceControlMap[InPieceData] = false;
	}
}