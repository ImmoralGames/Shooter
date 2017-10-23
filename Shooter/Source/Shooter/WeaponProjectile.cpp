// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponProjectile.h"
#include "Components/SphereComponent.h"
#include "PawnShip.h"
#include "PawnBuilding.h"
#include "DamageTypeBulletImpact.h"
#include "Shooter.h"
#include "Engine.h"

// Sets default values
AWeaponProjectile::AWeaponProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	this->bIsShot = false;

	USphereComponent* baseCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileBaseCollision"));

	this->BaseCollision = baseCollision;
	this->RootComponent = baseCollision;

	this->InitProjectileCollision();
}

void AWeaponProjectile::InitProjectileCollision()
{
	this->BaseCollision->InitSphereRadius(25);
	this->BaseCollision->CanCharacterStepUpOn = ECB_No;
	this->BaseCollision->SetCanEverAffectNavigation(false);

	this->BaseCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	this->BaseCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	this->BaseCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
}

// Called every frame
void AWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->bIsShot)
	{
		float distance = this->Speed * DeltaTime;
		FVector location = this->GetActorLocation();

		location += this->GetActorForwardVector() * distance;

		APawn* instigator = this->GetInstigator();
		if(instigator == nullptr)
		{
			this->Destroy();
			return;
		}

		int32 teamID = MONSTER_TEAM;
		if (instigator->GetClass()->IsChildOf(APawnShooter::StaticClass()))
			teamID = Cast<APawnShooter>(instigator)->GetTeamID();

		bool isTeamMonster = IS_MONSTER_TEAM(teamID);
		
		FHitResult hitResult;
		bool hitManaged = false;
		if (!this->SetActorLocation(location, true, &hitResult))
		{
			AActor* hitActor = hitResult.GetActor();
			if (hitActor != nullptr)
			{
				int32 hitTeamID = MONSTER_TEAM;
				if (hitActor->GetClass()->IsChildOf(APawnShooter::StaticClass()))
					hitTeamID = Cast<APawnShooter>(hitActor)->GetTeamID();

				bool isHitActorShip = hitActor->GetClass()->IsChildOf(APawnShip::StaticClass());
				bool isHitActorBuilding = hitActor->GetClass()->IsChildOf(APawnBuilding::StaticClass());
				
				if (teamID != hitTeamID || 
					(isHitActorShip && isTeamMonster && this->bFriendlyFireShipsMonster) ||
					(isHitActorShip && !isTeamMonster && this->bFriendlyFireShips) ||
					(isHitActorBuilding && isTeamMonster && this->bFriendlyFireBuildingMonster) ||
					(isHitActorBuilding && !isTeamMonster && this->bFriendlyFireBuilding))
				{					
					UGameplayStatics::ApplyPointDamage(hitActor, this->Damage, this->GetActorForwardVector(), hitResult, this->GetInstigatorController(), this, UDamageTypeBulletImpact::StaticClass());

					hitManaged = true;
					
#ifdef MUST_LOG_HITS
					if (GEngine)
					{
						FString debugMessage = TEXT("Hit an ennemy : ");
						debugMessage = debugMessage.Append(hitActor->GetName());
						GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, debugMessage);
					}
#endif
				}
				
				this->Destroy();
			}
			else
			{
#ifdef MUST_LOG_HITS
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Hit something (not actor)"));
#endif

				this->Destroy();
			}
		}
		else
		{
			this->TravelledDistance += distance;

			if (this->TravelledDistance >= this->Range)
			{
#ifdef MUST_LOG_HITS
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Hit range"));
#endif

				this->Destroy();
			}
		}
	}
}

void AWeaponProjectile::SetRange(int32 range)
{
	this->Range = range;
}

void AWeaponProjectile::SetDamage(int32 damage)
{
	this->Damage = damage;
}

void AWeaponProjectile::SetSpeed(int32 speed)
{
	this->Speed = speed;
}

void AWeaponProjectile::SetFriendlyFire(bool buildings, bool allies, bool monsterBuildings, bool monsterAllies)
{
	this->bFriendlyFireBuilding = buildings;
	this->bFriendlyFireShips = allies;
	this->bFriendlyFireBuildingMonster = monsterBuildings;
	this->bFriendlyFireShipsMonster = monsterAllies;
}

void AWeaponProjectile::Shoot_Implementation()
{
	this->bIsShot = true;
	this->BaseCollision->IgnoreActorWhenMoving(this->GetInstigator(), true);
	this->SetActorTickEnabled(true);
#ifdef MUST_LOG_HITS
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Pew!"));
#endif
}