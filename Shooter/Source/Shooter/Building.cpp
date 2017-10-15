// Fill out your copyright notice in the Description page of Project Settings.

#include "Building.h"
#include "DamageTypeExplosion.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"


// Sets default values
ABuilding::ABuilding()
{
	this->MaxHealth = this->Health = 100;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent *BaseCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BuildingBaseCollision"));
	BaseCollision->InitBoxExtent(FVector(50, 50, 50));
	BaseCollision->CanCharacterStepUpOn = ECB_No;

	this->RootComponent = BaseCollision;
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	this->Health = this->MaxHealth;
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::Explode()
{
	if (this->bCanExplode)
	{
		TArray<AActor*> actorsToIgnore = TArray<AActor*>();
		actorsToIgnore.Add(this);

		bool hasDamagedSomeone = UGameplayStatics::ApplyRadialDamage(this,
			this->ExplosionDamage, this->GetActorLocation(), this->ExplosionRange,
			TSubclassOf<UDamageType>(UDamageTypeExplosion::StaticClass()),
			actorsToIgnore, this, NULL,
			false, ECollisionChannel::ECC_Visibility);

		this->Destroy();
	}
}

TArray<APawnShip*> ABuilding::GetShipsInRange(float range) const
{
	TArray<APawnShip*> retval = TArray<APawnShip*>();

	const UWorld* const world = this->GetWorld();
	if (world == nullptr)
	{
		return retval;
	}

	APawn* pawn;
	APawnShip* ship;
	float distance;

	for (FConstPawnIterator itPawn = world->GetPawnIterator(); itPawn; ++itPawn)
	{
		pawn = itPawn->Get();
		if (pawn != nullptr)
		{
			ship = Cast<APawnShip>(pawn);
			if (ship != nullptr && ship->GetController()->IsPlayerController())
			{
				distance = this->GetDistanceTo(ship);

				if (distance < range)
				{
					retval.Add(ship);
				}
			}
		}
	}

	return retval;
}

float ABuilding::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	this->Health -= Damage;
	if (this->Health <= 0)
		this->Destroy();

	return Damage;
}