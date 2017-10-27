// Fill out your copyright notice in the Description page of Project Settings.

#include "PCompAutoExploder.h"
#include "DamageTypeExplosion.h"
#include "PawnShooter.h"
#include "PawnShip.h"
#include "PawnBuilding.h"
#include "Shooter.h"
#include "GameInstanceShooter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UPCompAutoExploder::UPCompAutoExploder()
{
	//PrimaryComponentTick.bCanEverTick = true;

	this->ExplosionDamage = 100;
	this->ExplosionRange = 1000;
	this->bCanExplode = false;
	
	this->bFriendlyFireShips = false;
	this->bFriendlyFireBuilding = false;
	this->bFriendlyFireShipsMonster = false;
	this->bFriendlyFireBuildingMonster = false;
}


void UPCompAutoExploder::Explode()
{
	const UWorld* const world = this->GetWorld();
	if (world == nullptr)
	{
		return;
	}
	
	APawnShooter* const owner = Cast<APawnShooter>(this->GetOwner());
	if (owner == nullptr)
	{
		return;
	}

	UGameInstanceShooter* gameInstance = Cast<UGameInstanceShooter>(owner->GetGameInstance());
	if (!gameInstance)
		return;
	
	if (this->bCanExplode)
	{		
		TArray<AActor*> actorsToIgnore = TArray<AActor*>();
		
		UClass* pawnClass;
		APawnShooter* shooter;
		bool isShip, isBuilding, isTeamMonster;
		
		int32 teamID = owner->GetTeamID();		
		isTeamMonster = IS_MONSTER_TEAM(teamID);
		
		TArray<APawnShooter*> teammates = gameInstance->GetAllies(teamID);
		for (auto It = teammates.CreateIterator(); It; ++It)
		{
			shooter = *It;
			if (shooter == owner)
				continue; // Will be ignored (see doc)

			pawnClass	= shooter->GetClass();
			isShip		= pawnClass->IsChildOf(APawnShip::StaticClass());
			isBuilding	= pawnClass->IsChildOf(APawnBuilding::StaticClass());
			
			if (isShip && isTeamMonster && this->bFriendlyFireShipsMonster)
				continue; // Let's damage

			if (isShip && !isTeamMonster && this->bFriendlyFireShips)
				continue; // Let's damage

			if (isBuilding && isTeamMonster && this->bFriendlyFireBuildingMonster)
				continue; // Let's damage

			if (isBuilding && !isTeamMonster && this->bFriendlyFireBuilding)
				continue; // Let's damage
			
			// Let's spare.
			actorsToIgnore.Add(shooter);
		}
				
		bool hasDamagedSomeone = UGameplayStatics::ApplyRadialDamage(this,
			this->ExplosionDamage, owner->GetActorLocation(), this->ExplosionRange,
			TSubclassOf<UDamageType>(UDamageTypeExplosion::StaticClass()),
			actorsToIgnore, owner, NULL,
			false, ECollisionChannel::ECC_Visibility);

		owner->Dead();
	}
}
