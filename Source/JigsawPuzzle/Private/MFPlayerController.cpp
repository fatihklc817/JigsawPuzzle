// Fill out your copyright notice in the Description page of Project Settings.


#include "JigsawPuzzle/Public/MFPlayerController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MFGameModeMain.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Grid/MFGridGenerator.h"


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

	

	//
	
	

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
			DrawDebugSphere(GetWorld(), Hit.Location, 10.0f, 10, FColor::Green, false, 2.f, 0, 1.0f);
			DrawDebugLine(GetWorld(), WorldOrigin, Hit.Location, FColor::Green, false, 2.f, 0, 1.0f);
			
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
	UE_LOG(LogTemp, Warning, TEXT("Clicked"));
	
	FVector WorldOrigin, WorldDirection;
	DeprojectMousePositionToWorld(WorldOrigin,WorldDirection);
	
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, WorldOrigin, WorldOrigin + WorldDirection * 10000, ECC_Visibility))
	{
		DrawDebugSphere(GetWorld(), Hit.Location, 10.0f, 10, FColor::Green, false, 10.f, 0, 1.0f);
		DrawDebugLine(GetWorld(), WorldOrigin, Hit.Location, FColor::Green, false, 10.f, 0, 1.0f);
		if (Hit.GetActor() && Hit.GetActor()->ActorHasTag("piece"))
		{
			OriginalZ = Hit.GetActor()->GetActorLocation().Z;
			SelectedPiece = Hit.GetActor();
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
	
	if (TOptional<FGridCell> GridCellResult = GridGenerator->GetGridCellAtGivenGridCoord(NearestGridCoord))
	{
		FGridCell GridCell = GridCellResult.GetValue();
		SelectedPiece->SetActorLocation(FVector(GridCell.Location.X, GridCell.Location.Y, OriginalZ));
		SelectedPiece = nullptr;
	}
	else
	{
		SelectedPiece->SetActorLocation(FVector(PieceLocation.X, PieceLocation.Y, OriginalZ));
		SelectedPiece = nullptr;
		
	}
	

}
