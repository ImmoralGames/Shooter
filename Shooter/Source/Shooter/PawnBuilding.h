// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "PawnShip.h"
#include "PawnTeamed.h"
#include "PawnBuilding.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SHOOTER_API APawnBuilding : public APawn, public IPawnTeamed
{
	GENERATED_BODY()

private:

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

	/** The building's team id */
	UPROPERTY(Category = "Team", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 TeamID;

private:
	UBoxComponent* BaseCollision;
	
public:	
	// Sets default values for this actor's properties
	APawnBuilding();

protected:

	UFUNCTION(Category = "Building|Construction", BlueprintCallable, meta = (DefaultToSelf))
	void InitBuildingCollision();

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

public:

	UFUNCTION(BlueprintCallable, Category = "Team")
	virtual int32 GetTeamID() const override;

	UFUNCTION(BlueprintCallable, Category = "Team")
	virtual void SetTeamID(int32 id) override;
};
