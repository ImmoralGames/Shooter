// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.h"
#include "PCompWeaponShooter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UPCompWeaponShooter : public USceneComponent
{
	GENERATED_BODY()
	
private:
	/** Actual time to wait to get a new charge */
	UPROPERTY(Category = "Weapon", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ReloadTimer;

	/** Actual time to wait before the shot */
	UPROPERTY(Category = "Weapon", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ShootingTimer;

	/** Actual time to wait before shooting a new time */
	UPROPERTY(Category = "Weapon", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CooldownTimer;

	/** Current charges the weapon shooter has stacked */
	UPROPERTY(Category = "Weapon", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 ChargesCount;
			
	UPROPERTY(Category = "Weapon", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsShooting;

private:
	UPROPERTY(Category = "Weapon", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWeapon* LoadedWeapon;

public:	
	UPCompWeaponShooter();	
	
private:
	void GetNewCharge();
	void OnShotFinished();

//protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

public:	
	
	void StartShooting();
	void StopShooting();
	void ShootAsap();
	
	bool HasWeaponLoaded();
	void SetWeapon(UWeapon* weapon);
	void SetWeapon(TSubclassOf<UWeapon> spellType);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
