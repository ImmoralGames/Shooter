// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "WeaponProjectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values for this component's properties
UWeapon::UWeapon()
{
	this->ShootTime = 0.1f;			// Instant charge cast
	this->CooldownTime = 0;			// Instant cooldown
	this->ChargesCountMax = 1;		// One stack spell
	this->ChargeReloadTime = 0.2f;	// 0.2f seconds
	this->bIsReloadable = true;		// Can reload charges
	this->bIsBasic = false;			// Not a basic weapon
	this->bReloadWhenEmpty = true;	// Basic reload mode
	this->ProjectileSpeed = 10000;
	this->ProjectileRange = 100000;
	this->ProjectileDamage = 10;
	this->bFriendlyFireShips = false;
	this->bFriendlyFireBuilding = false;
	this->bFriendlyFireShipsMonster = false;
	this->bFriendlyFireBuildingMonster = false;
}

AWeaponProjectile* UWeapon::MakeProjectile_Implementation(APawn* shooter, USceneComponent* shootingComponent)
{
	if (this->Projectile != NULL)
	{
		UWorld* world = shooter->GetWorld();
		UClass* projectileClass = this->Projectile;

		FActorSpawnParameters spawnParams = FActorSpawnParameters();
		spawnParams.Instigator = shooter;

		FVector location = shootingComponent->GetComponentLocation();
		FRotator rotation = shootingComponent->GetComponentRotation();
		location = location + shootingComponent->GetForwardVector() * 550;

		AWeaponProjectile* spawnedProjectile = world->SpawnActor<AWeaponProjectile>(
			projectileClass,
			location,
			rotation,
			spawnParams);

		return spawnedProjectile;
	}

	return NULL;
}

void UWeapon::Shot_Implementation(APawn* shooter, USceneComponent* shootingComponent)
{
	AWeaponProjectile* spawnedProjectile = this->MakeProjectile(shooter, shootingComponent);

	spawnedProjectile->SetSpeed(this->ProjectileSpeed);
	spawnedProjectile->SetRange(this->ProjectileRange);
	spawnedProjectile->SetDamage(this->ProjectileDamage);
	spawnedProjectile->Shoot();
}