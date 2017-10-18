// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "WeaponProjectile.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Weapons))
class SHOOTER_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()

private:

	/** Projectile to spawn on shoot */
	UPROPERTY(Category = "Weapon|Projectile", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float TravelledDistance;

	/** Projectile to spawn on shoot */
	UPROPERTY(Category = "Weapon|Projectile", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Range;
	
	/** Projectile to spawn on shoot */
	UPROPERTY(Category = "Weapon|Projectile", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Damage;

	/** Projectile to spawn on shoot */
	UPROPERTY(Category = "Weapon|Projectile", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 Speed;

	/** Is this projectile shot? */
	UPROPERTY(Category = "Weapon|Projectile", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsShot;

	/** Tells whether the projectile can damage allies */
	UPROPERTY(Category = "Weapon|Projectile", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireShips;

	/** Tells whether the projectile can damage allied buildings */
	UPROPERTY(Category = "Weapon|Projectile", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireBuilding;

	/** Tells whether the projectile can damage allies IF in monster team */
	UPROPERTY(Category = "Weapon|Projectile", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireShipsMonster;

	/** Tells whether the projectile can damage allied buildings IF in monster team*/
	UPROPERTY(Category = "Weapon|Projectile", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireBuildingMonster;

private:
	USphereComponent* BaseCollision;

public:	
	// Sets default values for this actor's properties
	AWeaponProjectile();

protected:

	UFUNCTION(Category = "Weapon|Construction", BlueprintCallable, meta = (DefaultToSelf))
	void InitProjectileCollision();

//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Weapon|Projectile")
	void SetRange(int32 projectileRange);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon|Projectile")
	void SetDamage(int32 projectileDamage);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon|Projectile")
	void SetSpeed(int32 projectileSpeed);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Projectile")
	void SetFriendlyFire(bool buildings, bool allies, bool monsterBuildings, bool monsterAllies);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon|Projectile")
	void Shoot();

protected:
	UFUNCTION(BlueprintCallable, Category = "Weapon|Projectile")
	virtual void Shoot_Implementation();

};
