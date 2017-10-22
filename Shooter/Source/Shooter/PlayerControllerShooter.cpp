// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerShooter.h"
#include "PawnShip.h"
#include "PawnBuilding.h"
#include "PawnGhost.h"
#include "Shooter.h"

void APlayerControllerShooter::SetupInputComponent()
{
	Super::SetupInputComponent();

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

 	FInputModeGameAndUI Mode;
#if WITH_EDITOR
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
#else
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
#endif
	Mode.SetHideCursorDuringCapture(false);
 
 	SetInputMode(Mode);

	bIsMouseLastDetected = true;
	
	InputComponent->BindAxis("MoveForward", this, &APlayerControllerShooter::MovePawnForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerControllerShooter::MovePawnRight);
	InputComponent->BindAxis("RotateSin", this, &APlayerControllerShooter::RotatePawnSin);
	InputComponent->BindAxis("RotateCos", this, &APlayerControllerShooter::RotatePawnCos);
	
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
	
	InputComponent->BindAction("EnableGodMode", IE_Pressed, this, &APlayerControllerShooter::EnableGodMode);
	InputComponent->BindAction("DisableGodMode", IE_Pressed, this, &APlayerControllerShooter::DisableGodMode);

}

void APlayerControllerShooter::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	float MouseX, MouseY;
	this->GetMousePosition(MouseX, MouseY);

	FVector2D MousePosition = FVector2D(MouseX, MouseY);
	FVector2D MouseDeltaPosition = LastMousePosition - MousePosition;
	LastMousePosition = MousePosition;
	
	bIsMouseLastDetected = (bIsMouseLastDetected || MouseDeltaPosition.SizeSquared() >= 0.01f);
	if(!bIsMouseLastDetected)
		return;
	
	APawn* pawn = this->GetPawn();
	if (pawn == nullptr)
		return;

	APawnShooter* pawnShooter = Cast<APawnShooter>(pawn);
	if (pawnShooter == nullptr)
		return;

	FVector location, direction;
	if (!this->DeprojectMousePositionToWorld(location, direction))
		return;

	FVector pawnLocation = pawn->GetActorLocation();

	// how many times shall we add 'direction' to 'location' 
	// in order to 'location.Z' and 'pawnLocation.Z' to be equals?
	float ratio = (pawnLocation.Z - location.Z) / direction.Z;

	location += direction * ratio;
	pawnShooter->LookAt(location);

}

void APlayerControllerShooter::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	auto pawn = Cast<APawnShooter>(aPawn);
	if (pawn)
	{
		pawn->SetTeamID(PLAYER_TEAM_1);

		auto ship = Cast<APawnShip>(pawn);
		if (ship)
		{
			this->OnPossessShip(ship);
			return;
		}

		auto building = Cast<APawnBuilding>(pawn);
		if (building)
		{
			this->OnPossessBuilding(building);
			return;
		}

		return;
	}

	auto ghost = Cast<APawnGhost>(aPawn);
	if (ghost)
	{
		this->OnPossessGhost(ghost);
		return;
	}
}

void APlayerControllerShooter::UnPossess()
{
	this->OnUnPossess();
	Super::UnPossess();
}

void APlayerControllerShooter::RotatePawnSin(const float Value)
{
	auto pawn = Cast<APawnShooter>(this->GetPawn());
	if (pawn)
	{
		pawn->AddInputRotationVector(FVector2D(0, Value));
		return;
	}

	if (Value > 0)
		bIsMouseLastDetected = false;
}

void APlayerControllerShooter::RotatePawnCos(const float Value)
{
	auto pawn = Cast<APawnShooter>(this->GetPawn());
	if (pawn)
	{
		pawn->AddInputRotationVector(FVector2D(Value, 0));
		return;
	}

	if (Value > 0)
		bIsMouseLastDetected = false;
}

void APlayerControllerShooter::MovePawnForward(const float Value)
{
	auto pawn = Cast<APawnShooter>(this->GetPawn());
	if (pawn)
	{
		pawn->AddInputVector(FVector(Value, 0, 0));
		return;
	}

	auto ghost = Cast<APawnGhost>(this->GetPawn());
	if (ghost)
	{
		ghost->AddInputVector(FVector(Value, 0, 0));
		return;
	}
}

void APlayerControllerShooter::MovePawnRight(const float Value)
{
	auto pawn = Cast<APawnShooter>(this->GetPawn());
	if (pawn)
	{
		pawn->AddInputVector(FVector(0, Value, 0));
		return;
	}

	auto ghost = Cast<APawnGhost>(this->GetPawn());
	if (ghost)
	{
		ghost->AddInputVector(FVector(0, Value, 0));
		return;
	}
}

void APlayerControllerShooter::EnableGodMode()
{
	auto pawn = Cast<APawnShooter>(this->GetPawn());
	if (pawn)
	{
		pawn->SetGodMode(true);
		return;
	}
}

void APlayerControllerShooter::DisableGodMode()
{
	auto pawn = Cast<APawnShooter>(this->GetPawn());
	if (pawn)
	{
		pawn->SetGodMode(false);
		return;
	}
}

void APlayerControllerShooter::CastSpellX()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CastSpellX();
		return;
	}
}


void APlayerControllerShooter::CastSpellY()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CastSpellY();
		return;
	}
}


void APlayerControllerShooter::CastSpellA()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CastSpellA();
		return;
	}
}


void APlayerControllerShooter::CastSpellB()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CastSpellB();
		return;
	}
}

void APlayerControllerShooter::CancelSpellX()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CancelSpellX();
		return;
	}
}


void APlayerControllerShooter::CancelSpellY()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CancelSpellY();
		return;
	}
}


void APlayerControllerShooter::CancelSpellA()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CancelSpellA();
		return;
	}
}


void APlayerControllerShooter::CancelSpellB()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->CancelSpellB();
		return;
	}
}

void APlayerControllerShooter::StartShootingBasicWeapon()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->StartShootingBasicWeapon();
		return;
	}
}

void APlayerControllerShooter::StopShootingBasicWeapon()
{
	auto pawn = Cast<APawnShip>(this->GetPawn());
	if (pawn)
	{
		pawn->StopShootingBasicWeapon();
		return;
	}
}