// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "UserWidgetHealthBar.h"
#include "WidgetComponent.h"
#include "PawnShooter.generated.h"

UCLASS(abstract, BlueprintType, Blueprintable)
class SHOOTER_API APawnShooter : public APawn
{
	GENERATED_BODY()

// Private properties
private:

	/** The pawn's health bar ui */
	UPROPERTY(Category = "PawnShooter", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidgetHealthBar> HealthBarSkin;

	/** The pawn's current health */
	UPROPERTY(Category = "PawnShooter", VisibleAnywhere, BlueprintReadOnly, Transient, meta = (AllowPrivateAccess = "true"))
	int32 Health;
	
	/** The pawn's current health */
	UPROPERTY(Category = "PawnShooter", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsGodMode;

	/** The pawn's max health */
	UPROPERTY(Category = "PawnShooter", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MaxHealth;

	/** Can the pawn explode? */
	UPROPERTY(Category = "PawnShooter", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanExplode;

	/** Explosion's damages */
	UPROPERTY(Category = "PawnShooter", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionDamage;

	/** Explosion's range */
	UPROPERTY(Category = "PawnShooter", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionRange;

	/** The pawn's team id */
	UPROPERTY(Category = "PawnShooter", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 TeamID;

// Protected references
private:
	UPROPERTY(Category = "PawnShooter", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UUserWidgetHealthBar* HealthBar;

protected:
	UPROPERTY(Category = "PawnShooter", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* HealthbarWidgetComponent;


	UBoxComponent* BaseCollision;

// Constructors
public:

	// Sets default values for this pawn's properties
	APawnShooter();

// Protected events
protected:

	virtual void Dead();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

// Public events
public:	

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

// Public commands
public:

	/** Add a directional command to the Movement component */
	UFUNCTION(Category = "Movement", BlueprintCallable)
	virtual void AddInputVector(const FVector& input) PURE_VIRTUAL(APawnShooter::AddInputVector, );

	/** Add a rotation command to the Movement component */
	UFUNCTION(Category = "Movement", BlueprintCallable)
	virtual void LookAt(const FVector& position) PURE_VIRTUAL(APawnShooter::LookAt,);

	/** Add a rotation command to the Movement component */
	UFUNCTION(Category = "Movement", BlueprintCallable)
	virtual void AddInputRotationVector(const FVector2D& input) PURE_VIRTUAL(APawnShooter::AddInputRotationVector, );

	/** Add a rotation command to the Movement component */
	UFUNCTION(Category = "Movement", BlueprintCallable)
	virtual void AddInputForwardVector(const FVector2D& input) PURE_VIRTUAL(APawnShooter::AddInputForwardVector, );
	
// Public getters
public:

	UFUNCTION(BlueprintCallable, Category = "Team")
	int32 GetTeamID() const;

	UFUNCTION(Category = "PawnShooter", BlueprintCallable, meta = (DefaultToSelf))
	TArray<APawnShooter*> GetPlayerPawnsInRange(float range) const;

	/** Returns the pawn's current health */
	UFUNCTION(Category = "Ship", BlueprintPure, meta = (DefaultToSelf))
	int32 GetCurrentHealth() const;

	/** Returns the pawn's max health */
	UFUNCTION(Category = "Ship", BlueprintPure, meta = (DefaultToSelf))
	int32 GetMaxHealth() const;

	/** Returns the pawn's current health (in percent of its max health) */
	UFUNCTION(Category = "Ship", BlueprintPure, meta = (DefaultToSelf))
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
