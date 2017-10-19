// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PawnShooter.h"
#include "PawnBuilding.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SHOOTER_API APawnBuilding : public APawnShooter
{
	GENERATED_BODY()

private:
	UBoxComponent* BaseCollision;
	
public:	
	// Sets default values for this actor's properties
	APawnBuilding();

protected:

	UFUNCTION(Category = "Building|Construction", BlueprintCallable, meta = (DefaultToSelf))
	void InitBuildingCollision();

};
