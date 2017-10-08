// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FloatingPawnMovementShip.h"
#include "PawnShip.generated.h"

UCLASS()
class SHOOTER_API APawnShip : public APawn
{
	GENERATED_BODY()

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

	UPROPERTY(Category = "Ship|Movement", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovementShip * MovementComponent;

public:
	// Sets default values for this pawn's properties
	APawnShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(Category = "Movement", BlueprintCallable)
	void AddInputVector(const FVector & input) const;
	
	
};
