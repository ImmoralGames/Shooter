// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "FloatingPawnMovementShip.h"
#include "GameFramework/SpringArmComponent.h"
#include "SpellCaster.h"
#include "WeaponShooter.h"
#include "PawnShooter.h"
#include "PawnShip.generated.h"

/** PawnShip is the base class of all ship pawns in a Shooter game */
UCLASS(BlueprintType, Blueprintable, meta = (ShortTooltip = "A PawnShip is a pawn that acts as a ship for a Shooter game."))
class SHOOTER_API APawnShip : public APawnShooter
{
	GENERATED_BODY()

// Private properties
private:

	/** The ship's base max speed */
	UPROPERTY(Category = "Ship|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BaseMaxSpeed;

	/** The ship's base acceleration */
	UPROPERTY(Category = "Ship|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float BaseAcceleration;


// Private reference properties
private:

	UBoxComponent* BaseCollision;

	/** The component that makes the ship move */
	UPROPERTY(Category = "Ship", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ModelComponent;

	/** The component that makes the ship move */
	UPROPERTY(Category = "Ship", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovementShip* MovementComponent;
	
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
	
// Protected Initializers
protected:

	UFUNCTION(Category = "Ship|Construction", BlueprintCallable, meta = (DefaultToSelf))
	void InitShipCollision();

// Protected events
protected:

	/** Called when a game starts */
	virtual void BeginPlay() override;
	

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
	
};
