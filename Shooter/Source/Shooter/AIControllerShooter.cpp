// Fill out your copyright notice in the Description page of Project Settings.

#include "AIControllerShooter.h"
#include "PawnShip.h"
#include "PawnBuilding.h"
#include "Engine/World.h"
#include "Shooter.h"

AAIControllerShooter::AAIControllerShooter()
{
	PrimaryActorTick.bCanEverTick = true;
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
	
	APawn* pawn;
	APawnShip* ship;
	APawnShip* nearest = nullptr;
	float nearestDistance = 0;
	
	for(FConstPawnIterator itPawn = world->GetPawnIterator(); itPawn; ++itPawn)
	{
		pawn = itPawn->Get();
		if (pawn != nullptr)
		{
			ship = Cast<APawnShip>(pawn);
			if (ship != nullptr && !IS_MONSTER_TEAM(ship->GetTeamID()))
			{
				distance = possessedShip->GetDistanceTo(ship);

				if (nearest == nullptr || nearestDistance > distance)
				{
					nearestDistance = distance;
					nearest = ship;
				}
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