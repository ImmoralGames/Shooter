// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnBuildingSpawner.h"
#include "SpellSpawn.h"


// Sets default values
APawnBuildingSpawner::APawnBuildingSpawner()
{
	this->SpawningSpell = NewObject<USpellSpawn>(
		(UObject*)GetTransientPackage(), 
		USpellSpawn::StaticClass());

	UPCompSpellCaster* spawnCaster = CreateDefaultSubobject<UPCompSpellCaster>(TEXT("SpawnCaster"));
	spawnCaster->SetupAttachment(RootComponent);
	spawnCaster->SetSpell(this->SpawningSpell);
	this->SpawnCaster = spawnCaster;

	SpawnPlace = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPlace"));
	SpawnPlace->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APawnBuildingSpawner::BeginPlay()
{
	Super::BeginPlay();
	if(this->SpawningSpell != NULL)
		this->SpawnCaster->SetSpell(this->SpawningSpell);
	this->SpawnCaster->SetWorldLocation(this->SpawnPlace->GetComponentLocation());
}

// Called every frame
void APawnBuildingSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->SpawnCaster->CanCast())
		this->SpawnCaster->CastSpell();

}
