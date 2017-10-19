// Fill out your copyright notice in the Description page of Project Settings.

#include "SpellSpawn.h"
#include "PawnShip.h"
#include "Runtime/Engine/Classes/Engine/World.h"

USpellSpawn::USpellSpawn() : USpell()
{

}

void USpellSpawn::Casted_Implementation(APawn* caster, USceneComponent* castingComponent)
{
	if (this->SpawnableShips.Num() == 0)
		return;

	UWorld* world = caster->GetWorld();

	int32 randomIndex = FMath::RandRange(0, this->SpawnableShips.Num() - 1);
	UClass* shipClass = this->SpawnableShips[randomIndex];
	
	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	
	APawnShip* spawnedShip = world->SpawnActor<APawnShip>(
		shipClass,
		castingComponent->GetComponentTransform(),
		spawnParams);
	
}