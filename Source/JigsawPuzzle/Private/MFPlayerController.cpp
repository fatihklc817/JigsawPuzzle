// Fill out your copyright notice in the Description page of Project Settings.


#include "JigsawPuzzle/Public/MFPlayerController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void AMFPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	
	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);

	if (FoundCameras.Num() > 0)
	{
		SetViewTarget(Cast<ACameraActor>(FoundCameras[0]));
	}	

}
