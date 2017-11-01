// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PawnShip.h"
#include "PawnBuilding.h"
#include "AIControllerShooter.generated.h"

/** AIControllerShooter is the base class of every AIController in a Shooter game */
UCLASS(BlueprintType, Abstract, Blueprintable, meta = (ShortTooltip = "A AIControllerShooter is the brain of an AI controlled Pawn for a Shooter game"))
class SHOOTER_API AAIControllerShooter : public AAIController
{
	GENERATED_BODY()

// Constructors
public:

	/** Constructs the basic components and sets the default controller properties */
	AAIControllerShooter();

// Public getters (helpers)
public:

	/** Returns the nearest player ship */
	UFUNCTION(Category="AI Tools", BlueprintPure, BlueprintCallable, meta = (DefaultToSelf))
	APawnShip* GetNearestPlayerShip() const;
	
	/** 
	  * Gets the nearest player ship and the distance between them 
	  * @param OutDistance The computed distance between the nearest player ship and the controlled ship
	  * @return Returns the nearest player ship
	  */
	UFUNCTION(Category="AI Tools", BlueprintPure, BlueprintCallable, meta = (DefaultToSelf))
	APawnShip* GetNearestPlayerShipWithDistance(float& OutDistance) const;

	/** Returns the controlled ship */
	UFUNCTION(Category = "AI Tools", BlueprintPure, BlueprintCallable, meta = (DefaultToSelf))
	APawnShip* GetShip() const;

	/** Returns the controlled building */
	UFUNCTION(Category = "AI Tools", BlueprintPure, BlueprintCallable, meta = (DefaultToSelf))
	APawnBuilding* GetBuilding() const;

// Public commands (helpers)
public:

	/** 
	  * Makes the current ship/building look at the given actor (if the controlled pawn can rotate)
	  * @param actor Actor to look at
	  */
	UFUNCTION(Category = "AI Tools", BlueprintCallable, meta = (DefaultToSelf))
	void LookAt(AActor* actor);
	
	/**
	  * Moves the controlled pawn towards the given actor (if the controlled pawn can move)
	  * @param actor Actor to move towards
	  */
	UFUNCTION(Category = "AI Tools", BlueprintCallable, meta = (DefaultToSelf))
	void GoTowardPosition(AActor* actor);
	
// Public events
public:


	/**
	  * Function called when the controller possesses a building pawn
	  * @param Controlled building
	  */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnPossessBuilding(APawnBuilding* building);

	/**
	  * Function called when the controller possesses a ship pawn
	  * @param Controlled ship
	  */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnPossessShip(APawnShip* ship);
	
	/**
	  * Function called when the controller possesses a pawn
	  * @param Controlled pawn
	  */
	virtual void Possess(APawn* pawn) override;
	
};
