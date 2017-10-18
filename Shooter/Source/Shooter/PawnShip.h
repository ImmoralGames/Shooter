// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "FloatingPawnMovementShip.h"
#include "GameFramework/SpringArmComponent.h"
#include "SpellCaster.h"
#include "WeaponShooter.h"
#include "PawnTeamed.h"
#include "PawnShip.generated.h"

/** PawnShip is the base class of all ship pawns in a Shooter game */
UCLASS(BlueprintType, Blueprintable, meta = (ShortTooltip = "A PawnShip is a pawn that acts as a ship for a Shooter game."))
class SHOOTER_API APawnShip : public APawn, public IPawnTeamed
{
	GENERATED_BODY()

// Private properties
private:
	
	/** The ship's current health */
	UPROPERTY(Category = "Ship|stats", VisibleAnywhere, BlueprintReadOnly, Transient, meta = (AllowPrivateAccess = "true"))
	int32 Health;

	/** The ship's max health */
	UPROPERTY(Category = "Ship|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MaxHealth;

	/** The ship's base max speed */
	UPROPERTY(Category = "Ship|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BaseMaxSpeed;

	/** The ship's base acceleration */
	UPROPERTY(Category = "Ship|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BaseAcceleration;

	/** Sets whether this ship can explode or not */
	UPROPERTY(Category = "Ship|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanExplode;

	/** The ship's explosion damage */
	UPROPERTY(Category = "Ship|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionDamage;

	/** The ship's explosion range */
	UPROPERTY(Category = "Ship|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionRange;

	/** The ship's team id */
	UPROPERTY(Category = "Team", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 TeamID;

// Private reference properties
private:

	UBoxComponent* BaseCollision;

	/** The component that makes the ship move */
	UPROPERTY(Category = "Ship|Movement", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovementShip * MovementComponent;
	
	/** The component that handles the camera movement */
	UPROPERTY(Category = "Ship", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraSpringArm;

	/** Spell caster (should be associated with the Y button) */
	UPROPERTY(Category = "Ship", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpellCaster* SpellCasterY;

	/** Spell caster (should be associated with the X button) */
	UPROPERTY(Category = "Ship", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpellCaster* SpellCasterX;

	/** Spell caster (should be associated with the A button) */
	UPROPERTY(Category = "Ship", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpellCaster* SpellCasterA;

	/** Spell caster (should be associated with the B button) */
	UPROPERTY(Category = "Ship", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpellCaster* SpellCasterB;

	/** Spell caster (should be associated with the B button) */
	UPROPERTY(Category = "Ship", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWeaponShooter* BasicWeaponShooter;

// Constructors
public:

	/** Constructs the basic components and sets the default ship properties */
	APawnShip();
	
protected:

	UFUNCTION(Category = "Ship|Construction", BlueprintCallable, meta = (DefaultToSelf))
	void InitShipCollision();

// Public Getters
public:

	/** Returns the ships around this given ship, at the given range (or less) */
	UFUNCTION(Category = "AI Tools", BlueprintCallable, meta = (DefaultToSelf))
	TArray<APawnShip*> GetShipsInRange(float range) const;

	/** Returns the ship's current health */
	UFUNCTION(Category = "Ship|stats", BlueprintPure, meta = (DefaultToSelf))
	int32 GetCurrentHealth() const;

	/** Returns the ship's max health */
	UFUNCTION(Category = "Ship|stats", BlueprintPure, meta = (DefaultToSelf))
	int32 GetMaxHealth() const;

	/** Returns the ship's current health (in percent of its max health) */
	UFUNCTION(Category = "Ship|stats", BlueprintPure, meta = (DefaultToSelf))
	float GetPercentHealth() const;

	/** Returns the ship's team ID */
	UFUNCTION(BlueprintCallable, Category = "Team")
	virtual int32 GetTeamID() const override;

// Public Setters
public:

	/** Sets the ship's team ID */
	UFUNCTION(BlueprintCallable, Category = "Team")
	virtual void SetTeamID(int32 id) override;

// Protected events
protected:

	/** Called when a game starts */
	virtual void BeginPlay() override;

// Public Events
public:		

	/** Called to update the ship' state */
	virtual void Tick(float DeltaTime) override;

	/** Called when the sip shall take damages */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

// Public commands
public:

	/** Called to cast the spell that should be associated to the X button */
	void CastSpellX();

	/** Called to cast the spell that should be associated to the Y button */
	void CastSpellY();

	/** Called to cast the spell that should be associated to the A button */
	void CastSpellA();

	/** Called to cast the spell that should be associated to the B button */
	void CastSpellB();

	/** Called to cancel the cast of the spell that should be associated to the X button */
	void CancelSpellX();

	/** Called to cancel the cast of the spell that should be associated to the Y button */
	void CancelSpellY();

	/** Called to cancel the cast of the spell that should be associated to the A button */
	void CancelSpellA();

	/** Called to cancel the cast of the spell that should be associated to the B button */
	void CancelSpellB();

	/** Shoots a normal bullet */
	virtual void ShootBasicWeapon();

	/** Starts shooting normal bullets */
	virtual void StartShootingBasicWeapon();

	/** Stops shooting normal bullets */
	virtual void StopShootingBasicWeapon();
	
	/** Add a directional command to the Movement component */
	UFUNCTION(Category = "Movement", BlueprintCallable)
	void AddInputVector(const FVector & input) const;

	/** Asks the ship to explode */
	UFUNCTION(Category = "AI Tools", BlueprintCallable, meta = (DefaultToSelf))
	void Explode();

	
};
