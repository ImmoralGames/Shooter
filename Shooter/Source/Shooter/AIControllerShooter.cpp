// Ascii banners made with Bagill's ASCII Signature Generator using the Font: "Small" (width:53)

// ___________________________________________________ //
//           ___         _         _                   //
//          |_ _|_ _  __| |_  _ __| |___ ___           //
//           | || ' \/ _| | || / _` / -_|_-<           //
//          |___|_||_\__|_|\_,_\__,_\___/__/           //
// ___________________________________________________ //

#include "AIControllerShooter.h"
#include "Engine/World.h"
#include "Shooter.h"
#include "GameInstanceShooter.h"

// ___________________________________________________ //
//    ___             _               _                //
//   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _ ___  //
//  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_(_-<  //
//   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_| /__/  //
// ___________________________________________________ //

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


// ___________________________________________________ //
//              ___     _   _                          //
//             / __|___| |_| |_ ___ _ _ ___            //
//            | (_ / -_)  _|  _/ -_) '_(_-<            //
//             \___\___|\__|\__\___|_| /__/            //
// ___________________________________________________ //

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

// ___________________________________________________ //
//        ___                              _           //
//       / __|___ _ __  _ __  __ _ _ _  __| |___       //
//      | (__/ _ \ '  \| '  \/ _` | ' \/ _` (_-<       //
//       \___\___/_|_|_|_|_|_\__,_|_||_\__,_/__/       //
// ___________________________________________________ //

void AAIControllerShooter::LookAt(AActor* actor)
{
	if (actor == nullptr)
		return;

	APawnShip* const possessedShip = GetShip();
	if (possessedShip != nullptr)
		possessedShip->LookAt(actor->GetActorLocation());

}

void AAIControllerShooter::GoTowardPosition(AActor* actor)
{
	if (actor == nullptr)
		return;

	APawnShip* const possessedShip = GetShip();
	if (possessedShip != nullptr)
		possessedShip->GoTowardPosition(actor->GetActorLocation());
}
