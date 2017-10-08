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

	UPROPERTY(Category = "Ship|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanExplode;

	UPROPERTY(Category = "Ship|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionDamage;

	UPROPERTY(Category = "Ship|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionRange;

	UPROPERTY(Category = "Ship|Movement", BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovementShip * MovementComponent;
		
// Constructors
public:
	// Sets default values for this pawn's properties
	APawnShip();

// Protected events
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// Public Events
public:	
		
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

// Public methods
public:
	
	UFUNCTION(Category = "Movement", BlueprintCallable)
	void AddInputVector(const FVector & input) const;

	UFUNCTION(Category = "AI Tools", BlueprintCallable, meta = (DefaultToSelf))
	void Explode();

	UFUNCTION(Category = "AI Tools", BlueprintCallable, meta = (DefaultToSelf))
	TArray<APawnShip*> GetShipsInRange(float range) const;
};
