// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponMiniShootingGun.h"
#include "WeaponProjectileGunBullet.h"

UWeaponMiniShootingGun::UWeaponMiniShootingGun()
{
	this->Projectile = AWeaponProjectileGunBullet::StaticClass();
}

