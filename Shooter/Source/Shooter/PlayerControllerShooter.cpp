// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerShooter.h"
#include "PawnShip.h"



void APlayerControllerShooter::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &APlayerControllerShooter::MoveShipForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerControllerShooter::MoveShipRight);

	InputComponent->BindAction("CastSpellX", IE_Pressed, this, &APlayerControllerShooter::CastSpellX);
	InputComponent->BindAction("CastSpellX", IE_Released, this, &APlayerControllerShooter::CancelSpellX);
	InputComponent->BindAction("CastSpellY", IE_Pressed, this, &APlayerControllerShooter::CastSpellY);
	InputComponent->BindAction("CastSpellY", IE_Released, this, &APlayerControllerShooter::CancelSpellY);
	InputComponent->BindAction("CastSpellA", IE_Pressed, this, &APlayerControllerShooter::CastSpellA);
	InputComponent->BindAction("CastSpellA", IE_Released, this, &APlayerControllerShooter::CancelSpellA);
	InputComponent->BindAction("CastSpellB", IE_Pressed, this, &APlayerControllerShooter::CastSpellB);
	InputComponent->BindAction("CastSpellB", IE_Released, this, &APlayerControllerShooter::CancelSpellB);
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

void APlayerControllerShooter::CastSpellX()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CastSpellX();
	}
}


void APlayerControllerShooter::CastSpellY()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CastSpellY();
	}
}


void APlayerControllerShooter::CastSpellA()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CastSpellA();
	}
}


void APlayerControllerShooter::CastSpellB()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CastSpellB();
	}
}

void APlayerControllerShooter::CancelSpellX()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CancelSpellX();
	}
}


void APlayerControllerShooter::CancelSpellY()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CancelSpellY();
	}
}


void APlayerControllerShooter::CancelSpellA()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CancelSpellA();
	}
}


void APlayerControllerShooter::CancelSpellB()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CancelSpellB();
	}
}