// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "PawnShip.h"



void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveShipForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveShipRight);
}

void AMyPlayerController::MoveShipForward(const float Value)
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->AddInputVector(FVector(Value, 0, 0));
	}
}

void AMyPlayerController::MoveShipRight(const float Value)
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->AddInputVector(FVector(0, Value, 0));
	}
}