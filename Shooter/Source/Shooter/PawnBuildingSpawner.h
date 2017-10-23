// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PawnBuilding.h"
#include "PCompSpellCaster.h"
#include "SpellSpawn.h"
#include "Components/ArrowComponent.h"
#include "PawnBuildingSpawner.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SHOOTER_API APawnBuildingSpawner : public APawnBuilding
{
	GENERATED_BODY()

private:
	UPCompSpellCaster* SpawnCaster;

	UPROPERTY(Category = "Building", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* SpawnPlace;
public:	
	// Sets default values for this actor's properties
	APawnBuildingSpawner();

	UPROPERTY(Category = "Building", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpellSpawn* SpawningSpell;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
