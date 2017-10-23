// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnShooter.h"
#include "PawnBuilding.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SHOOTER_API APawnBuilding : public APawnShooter
{
	GENERATED_BODY()
			
public:	
	// Sets default values for this actor's properties
	APawnBuilding();

protected:

	UFUNCTION(Category = "Building|Construction", BlueprintCallable, meta = (DefaultToSelf))
	void InitBuildingCollision();

	/** Add a directional command to the Movement component */
	UFUNCTION(Category = "Movement", BlueprintCallable)
	virtual void AddInputVector(const FVector& input) override;

	/** Add a rotation command to the Movement component */
	UFUNCTION(Category = "Movement", BlueprintCallable)
	virtual void AddInputRotationVector(const FVector2D& input) override;

	/** Add a rotation command to the Movement component */
	UFUNCTION(Category = "Movement", BlueprintCallable)
	virtual void AddInputForwardVector(const FVector2D& input) override;

};
