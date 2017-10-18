// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnBuildingSpawner.h"
#include "PawnBuilding.h"
#include "SpellSpawn.h"


// Sets default values
APawnBuildingSpawner::APawnBuildingSpawner()
{
	this->SpawningSpell = NewObject<USpellSpawn>(
		(UObject*)GetTransientPackage(), 
		USpellSpawn::StaticClass());

	USpellCaster* spawnCaster = CreateDefaultSubobject<USpellCaster>(TEXT("SpawnCaster"));
	spawnCaster->SetSpell(this->SpawningSpell);

	this->SpawnCaster = spawnCaster;
}

// Called when the game starts or when spawned
void APawnBuildingSpawner::BeginPlay()
{
	Super::BeginPlay();
	if(this->SpawningSpell != NULL)
		this->SpawnCaster->SetSpell(this->SpawningSpell);
}

// Called every frame
void APawnBuildingSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->SpawnCaster->CanCast())
		this->SpawnCaster->CastSpell();

}
