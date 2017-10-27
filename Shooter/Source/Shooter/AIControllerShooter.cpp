// Fill out your copyright notice in the Description page of Project Settings.

#include "AIControllerShooter.h"
#include "PawnShip.h"
#include "PawnBuilding.h"
#include "Engine/World.h"
#include "Shooter.h"
#include "GameInstanceShooter.h"

AAIControllerShooter::AAIControllerShooter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIControllerShooter::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	auto pawn = Cast<APawnShooter>(aPawn);
	if (pawn)
	{
		pawn->SetTeamID(MONSTER_TEAM);

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

	}
}


APawnShip* AAIControllerShooter::GetShip() const 
{
	APawn* const pawn = this->GetPawn();
	if (pawn == nullptr)
	{
		return nullptr;
	}
	
	return Cast<APawnShip>(pawn);
}

APawnBuilding* AAIControllerShooter::GetBuilding() const
{
	APawn* const pawn = this->GetPawn();
	if (pawn == nullptr)
	{
		return nullptr;
	}

	return Cast<APawnBuilding>(pawn);
}

APawnShip* AAIControllerShooter::GetNearestPlayerShip() const
{
	float distance;
	return this->GetNearestPlayerShipWithDistance(distance);
}

APawnShip* AAIControllerShooter::GetNearestPlayerShipWithDistance(float& distance) const
{
	const APawnShip* const possessedShip = GetShip();
	if (possessedShip == nullptr)
	{
		return nullptr;
	}

	const UWorld* const world = this->GetWorld();
	if (world == nullptr)
	{
		return nullptr;
	}
	
	APawnShooter* shooter;
	APawnShip* ship;
	APawnShip* nearest = nullptr;
	float nearestDistance = 0;

	UGameInstanceShooter* gameInstance = Cast<UGameInstanceShooter>(this->GetGameInstance());
	if (gameInstance == nullptr)
		return nullptr;

	TArray<APawnShooter*> players = gameInstance->GetPlayers();
	for (auto It = players.CreateIterator(); It; ++It)
	{
		shooter = *It;
		if (shooter == nullptr)
			continue;

		ship = Cast<APawnShip>(shooter);
		if (ship != nullptr)
		{
			distance = possessedShip->GetDistanceTo(ship);

			if (nearest == nullptr || nearestDistance > distance)
			{
				nearestDistance = distance;
				nearest = ship;
			}
		}
	}

	return nearest;
}

void AAIControllerShooter::LookAt(AActor* actor)
{
	if(actor == nullptr)
		return;
	
	APawnShip* const possessedShip = GetShip();
	if (possessedShip != nullptr)
		possessedShip->LookAt(actor->GetActorLocation());

}

void AAIControllerShooter::GoTowardPosition(AActor* actor)
{
	if(actor == nullptr)
		return;
	
	APawnShip* const possessedShip = GetShip();
	if (possessedShip != nullptr)
		possessedShip->GoTowardPosition(actor->GetActorLocation());
}