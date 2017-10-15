// Fill out your copyright notice in the Description page of Project Settings.

#include "SpellCasterSpawn.h"
#include "PawnShip.h"
#include "Runtime/Engine/Classes/Engine/World.h"

USpellCasterSpawn::USpellCasterSpawn() : USpellCaster()
{

}

void USpellCasterSpawn::DoSpellAction()
{
	if (this->SpawnableShips.Num() == 0)
		return;

	UWorld* world = this->GetWorld();

	int32 randomIndex = FMath::RandRange(0, this->SpawnableShips.Num() - 1);
	UClass* shipClass = this->SpawnableShips[randomIndex];
	
	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	
	APawnShip* spawnedShip = world->SpawnActor<APawnShip>(
		shipClass,
		this->GetOwner()->GetTransform(),
		spawnParams);
	
}