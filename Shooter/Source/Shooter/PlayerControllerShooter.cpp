// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerShooter.h"
#include "PawnShip.h"
#include "PawnShooter.h"
#include "Shooter.h"


void APlayerControllerShooter::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewport(true);
	Mode.SetHideCursorDuringCapture(false);
	SetInputMode(Mode);

	InputComponent->BindAxis("MoveForward", this, &APlayerControllerShooter::MoveShipForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerControllerShooter::MoveShipRight);
	InputComponent->BindAxis("RotateSin", this, &APlayerControllerShooter::RotateShipSin);
	InputComponent->BindAxis("RotateCos", this, &APlayerControllerShooter::RotateShipCos);

	InputComponent->BindAction("CastSpellX", IE_Pressed, this, &APlayerControllerShooter::CastSpellX);
	InputComponent->BindAction("CastSpellX", IE_Released, this, &APlayerControllerShooter::CancelSpellX);
	InputComponent->BindAction("CastSpellY", IE_Pressed, this, &APlayerControllerShooter::CastSpellY);
	InputComponent->BindAction("CastSpellY", IE_Released, this, &APlayerControllerShooter::CancelSpellY);
	InputComponent->BindAction("CastSpellA", IE_Pressed, this, &APlayerControllerShooter::CastSpellA);
	InputComponent->BindAction("CastSpellA", IE_Released, this, &APlayerControllerShooter::CancelSpellA);
	InputComponent->BindAction("CastSpellB", IE_Pressed, this, &APlayerControllerShooter::CastSpellB);
	InputComponent->BindAction("CastSpellB", IE_Released, this, &APlayerControllerShooter::CancelSpellB);
	InputComponent->BindAction("BasicShoot", IE_Pressed, this, &APlayerControllerShooter::StartShootingBasicWeapon);
	InputComponent->BindAction("BasicShoot", IE_Released, this, &APlayerControllerShooter::StopShootingBasicWeapon);

}

void APlayerControllerShooter::Possess(APawn* aPawn)
{
	auto pawn = Cast<APawnShooter>(this->GetPawn());
	if (pawn)
	{
		pawn->SetTeamID(PLAYER_TEAM_1);
	}

	Super::Possess(aPawn);
}

void APlayerControllerShooter::RotateShipSin(const float Value)
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->AddInputRotationVector(FVector2D(0, Value));
	}
}

void APlayerControllerShooter::RotateShipCos(const float Value)
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->AddInputRotationVector(FVector2D(Value, 0));
	}
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

void APlayerControllerShooter::StartShootingBasicWeapon()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->StartShootingBasicWeapon();
	}
}

void APlayerControllerShooter::StopShootingBasicWeapon()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->StopShootingBasicWeapon();
	}
}