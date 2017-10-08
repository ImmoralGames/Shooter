// Fill out your copyright notice in the Description page of Project Settings.

#include "AIControllerShooter.h"
#include "PawnShip.h"
#include "Engine/World.h"

AAIControllerShooter::AAIControllerShooter()
{
	PrimaryActorTick.bCanEverTick = true;
}

APawnShip* AAIControllerShooter::GetShip() const 
{
	APawn* pawn = this->GetPawn();
	if (pawn == nullptr)
	{
		return nullptr;
	}
	
	return Cast<APawnShip>(pawn);
}

APawnShip* AAIControllerShooter::GetNearestPlayerShip() const
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
	float nearestDistance;
	float distance;
	
	for(FConstPawnIterator itPawn = world->GetPawnIterator(); itPawn; ++itPawn)
	{
		pawn = itPawn->Get();
		if (pawn != nullptr)
		{
			ship = Cast<APawnShip>(pawn);
			if (ship != nullptr && ship->GetController()->IsPlayerController())
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
