// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingSpawner.h"
#include "Building.h"
#include "SpellSpawn.h"


// Sets default values
ABuildingSpawner::ABuildingSpawner() : ABuilding()
{
	this->SpawningSpell = NewObject<USpellSpawn>(
		(UObject*)GetTransientPackage(), 
		USpellSpawn::StaticClass());

	USpellCaster* spawnCaster = CreateDefaultSubobject<USpellCaster>(TEXT("SpawnCaster"));
	spawnCaster->SetSpell(this->SpawningSpell);

	this->SpawnCaster = spawnCaster;
}

// Called when the game starts or when spawned
void ABuildingSpawner::BeginPlay()
{
	Super::BeginPlay();
	if(this->SpawningSpell != NULL)
		this->SpawnCaster->SetSpell(this->SpawningSpell);
}

// Called every frame
void ABuildingSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->SpawnCaster->CanCast())
		this->SpawnCaster->CastSpell();

}
