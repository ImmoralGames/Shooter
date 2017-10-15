// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PawnShip.h"
#include "Building.generated.h"

UCLASS()
class SHOOTER_API ABuilding : public AActor
{
	GENERATED_BODY()

	/** The building's current health */
	UPROPERTY(Category = "Building|stats", VisibleAnywhere, BlueprintReadOnly, Transient, meta = (AllowPrivateAccess = "true"))
	int32 Health;

	/** The building's max health */
	UPROPERTY(Category = "Building|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MaxHealth;

	/** Can the building explode? */
	UPROPERTY(Category = "Building|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanExplode;

	/** Explosion's damages */
	UPROPERTY(Category = "Building|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionDamage;

	/** Explosion's range */
	UPROPERTY(Category = "Building|stats", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionRange;

	
public:	
	// Sets default values for this actor's properties
	ABuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Category = "AI Tools", BlueprintCallable, meta = (DefaultToSelf))
	void Explode();

	UFUNCTION(Category = "AI Tools", BlueprintCallable, meta = (DefaultToSelf))
	TArray<APawnShip*> GetShipsInRange(float range) const;	
};
