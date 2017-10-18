// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponMiniShootingGun.h"
#include "Engine.h"
#include "WeaponProjectileGunBullet.h"

UWeaponMiniShootingGun::UWeaponMiniShootingGun()
{
	this->Projectile = AWeaponProjectileGunBullet::StaticClass();
}


void UWeaponMiniShootingGun::Shot_Implementation(AActor* shooter)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Pew!"));

	this->MakeProjectile(shooter);
}
