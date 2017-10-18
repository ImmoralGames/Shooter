// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnBuilding.h"
#include "DamageTypeExplosion.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Shooter.h"


// Sets default values
APawnBuilding::APawnBuilding()
{
	this->MaxHealth = this->Health = 100;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent* baseCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BuildingBaseCollision"));
	baseCollision->SetMobility(EComponentMobility::Static);

	this->BaseCollision = baseCollision;
	this->RootComponent = baseCollision;

	this->TeamID = MONSTER_TEAM;
	this->InitBuildingCollision();
}

void APawnBuilding::InitBuildingCollision()
{
	this->BaseCollision->InitBoxExtent(FVector(500, 500, 500));
	this->BaseCollision->CanCharacterStepUpOn = ECB_No;
	this->BaseCollision->SetCanEverAffectNavigation(false);

	this->BaseCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	this->BaseCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	this->BaseCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
}

int32 APawnBuilding::GetTeamID() const
{
	return this->TeamID;
}

void APawnBuilding::SetTeamID(int32 teamID)
{
	this->TeamID = teamID;
}

// Called when the game starts or when spawned
void APawnBuilding::BeginPlay()
{
	Super::BeginPlay();

	this->Health = this->MaxHealth;
	
}

// Called every frame
void APawnBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APawnBuilding::Explode()
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

TArray<APawnShip*> APawnBuilding::GetShipsInRange(float range) const
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

float APawnBuilding::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	this->Health -= Damage;
	if (this->Health <= 0)
		this->Destroy();

	return Damage;
}