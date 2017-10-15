// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingSpawner.h"
#include "Building.h"
#include "SpellCasterSpawn.h"


// Sets default values
ABuildingSpawner::ABuildingSpawner() : ABuilding()
{
	USpellCasterSpawn* spawnCaster = CreateDefaultSubobject<USpellCasterSpawn>(TEXT("SpawnCaster"));
	
	this->SpawnCaster = spawnCaster;
}

// Called when the game starts or when spawned
void ABuildingSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->SpawnCaster->CanCast())
		this->SpawnCaster->CastSpell();

}
