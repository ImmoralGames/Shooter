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
}

void UWeapon::MakeProjectile_Implementation(AActor* shooter)
{
	if (this->Projectile != NULL)
	{
		UWorld* world = shooter->GetWorld();
		UClass* projectileClass = this->Projectile;

		FActorSpawnParameters spawnParams = FActorSpawnParameters();

		AWeaponProjectile* spawnedProjectile = world->SpawnActor<AWeaponProjectile>(
			projectileClass,
			shooter->GetTransform(),
			spawnParams);
	}
}