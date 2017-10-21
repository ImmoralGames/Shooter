// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnShooter.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "PawnGhost.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SHOOTER_API APawnGhost : public APawn
{
	GENERATED_BODY()
	
private:


	/** The component that makes the ghost move */
	UPROPERTY(Category = "PawnGhost", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* MovementComponent;
	
	/** The component that handles the camera movement */
	UPROPERTY(Category = "PawnGhost", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraSpringArm;

private:
	UPROPERTY(Category = "PawnGhost", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APawnShooter> ResurrectType;

	UPROPERTY(Category = "PawnGhost", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float TimeBeforeResurrection;

	UPROPERTY(Category = "PawnGhost", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ResurrectionTimer;

// Constructors
public:

	/** Constructs the basic components and sets the default ghost properties */
	APawnGhost();

	UFUNCTION(Category = "PawnGhost", BlueprintCallable)
	void InitResurrection(float timer, TSubclassOf<APawnShooter> type);

	// Called every frame
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	
	virtual void Resurrect();

// Public commands
public:

	/** Add a directional command to the Movement component */
	UFUNCTION(Category = "Movement", BlueprintCallable)
	void AddInputVector(const FVector & input) const;

};
