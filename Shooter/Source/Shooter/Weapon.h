// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Engine/DataAsset.h"
#include "WeaponProjectile.h"
#include "Weapon.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Weapons))
class SHOOTER_API UWeapon : public UDataAsset
{
	GENERATED_BODY()

public:

	/** Projectile to spawn on shoot */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponProjectile> Projectile;

	/** Time to wait to have a new charge */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ChargeReloadTime;

	/** Time to wait after shooting the weapon for the projectile to spawn */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ShootTime;

	/** Time to wait after a projectile spawn before shooting a new time */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CooldownTime;

	/** Max charges the weapon can stack */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 ChargesCountMax;

	/** Tells whether the weapon can reload its bullet stack or not */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsReloadable;

	/** Tells whether the weapon  is a basic weapon or not */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsBasic;

	/** Tells whether the weapon can reload its bullet stack or not only if empty */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bReloadWhenEmpty;
	
	/** Tells whether the weapon can damage allies */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireShips;

	/** Tells whether the weapon can damage allied buildings */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireBuilding;

	/** Tells whether the weapon can damage allies IF in monster team */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireShipsMonster;

	/** Tells whether the weapon can damage allied buildings IF in monster team*/
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireBuildingMonster;
	
	/** Max charges the weapon can stack */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 ProjectileDamage;

	/** Max charges the weapon can stack */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 ProjectileSpeed;

	/** Max charges the weapon can stack */
	UPROPERTY(Category = "Weapon|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 ProjectileRange;

protected:
	UWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Shot_Implementation(APawn* shooter);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual AWeaponProjectile* MakeProjectile_Implementation(APawn* shooter);

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	AWeaponProjectile* MakeProjectile(APawn* shooter);

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void Shot(APawn* shooter);

};
