// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Engine/DataAsset.h"
#include "WeaponProjectile.h"
#include "Weapon.generated.h"


UCLASS(abstract, Blueprintable, BlueprintType, ClassGroup = (Weapons))
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

protected:
	UWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Shot_Implementation(AActor* shooter) PURE_VIRTUAL(UWeapon::Shot_Implementation, );

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void MakeProjectile_Implementation(AActor* shooter);

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void MakeProjectile(AActor* shooter);

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void Shot(AActor* shooter);

};
