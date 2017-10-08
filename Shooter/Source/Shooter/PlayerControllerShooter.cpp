// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerShooter.h"
#include "PawnShip.h"



void APlayerControllerShooter::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &APlayerControllerShooter::MoveShipForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerControllerShooter::MoveShipRight);
}

void APlayerControllerShooter::MoveShipForward(const float Value)
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->AddInputVector(FVector(Value, 0, 0));
	}
}

void APlayerControllerShooter::MoveShipRight(const float Value)
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->AddInputVector(FVector(0, Value, 0));
	}
}