// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnShooter.generated.h"

UCLASS(abstract, BlueprintType, Blueprintable)
class SHOOTER_API APawnShooter : public APawn
{
	GENERATED_BODY()

// Private properties
private:

	/** The building's current health */
	UPROPERTY(Category = "PawnShooter", VisibleAnywhere, BlueprintReadOnly, Transient, meta = (AllowPrivateAccess = "true"))
	int32 Health;
	
	/** The building's current health */
	UPROPERTY(Category = "PawnShooter", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsGodMode;

	/** The building's max health */
	UPROPERTY(Category = "PawnShooter", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MaxHealth;

	/** Can the building explode? */
	UPROPERTY(Category = "PawnShooter", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanExplode;

	/** Explosion's damages */
	UPROPERTY(Category = "PawnShooter", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionDamage;

	/** Explosion's range */
	UPROPERTY(Category = "PawnShooter", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionRange;

	/** The building's team id */
	UPROPERTY(Category = "PawnShooter", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 TeamID;

// Constructors
public:

	// Sets default values for this pawn's properties
	APawnShooter();

// Protected events
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

// Public events
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
// Public getters
public:

	UFUNCTION(BlueprintCallable, Category = "Team")
	int32 GetTeamID() const;

	UFUNCTION(Category = "PawnShooter", BlueprintCallable, meta = (DefaultToSelf))
	TArray<APawnShooter*> GetPlayerPawnsInRange(float range) const;

	/** Returns the pawn's current health */
	UFUNCTION(Category = "Ship|stats", BlueprintPure, meta = (DefaultToSelf))
	int32 GetCurrentHealth() const;

	/** Returns the pawn's max health */
	UFUNCTION(Category = "Ship|stats", BlueprintPure, meta = (DefaultToSelf))
	int32 GetMaxHealth() const;

	/** Returns the pawn's current health (in percent of its max health) */
	UFUNCTION(Category = "Ship|stats", BlueprintPure, meta = (DefaultToSelf))
	float GetPercentHealth() const;

// Public setters
public:

	UFUNCTION(BlueprintCallable, Category = "Team")
	void SetTeamID(int32 newTeamID);

// Commands
public:

	UFUNCTION(Category = "PawnShooter", BlueprintCallable, meta = (DefaultToSelf))
	void Explode();
};
