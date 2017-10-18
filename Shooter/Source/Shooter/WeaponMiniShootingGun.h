// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponMiniShootingGun.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UWeaponMiniShootingGun : public UWeapon
{
	GENERATED_BODY()

public:
	UWeaponMiniShootingGun();
	
protected:

	virtual void Shot_Implementation(AActor* shooter) override;
	
	
};
