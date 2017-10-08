// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PawnShip.h"
#include "AIControllerShooter.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Abstract, Blueprintable)
class SHOOTER_API AAIControllerShooter : public AAIController
{
	GENERATED_BODY()
	
public:

	AAIControllerShooter();

	UFUNCTION(Category="AI Tools", BlueprintPure, BlueprintCallable, meta = (DefaultToSelf))
	APawnShip* GetNearestPlayerShip() const;

	UFUNCTION(Category = "AI Tools", BlueprintPure, BlueprintCallable, meta = (DefaultToSelf))
	APawnShip* GetShip() const;
	
};
