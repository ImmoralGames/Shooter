// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.h"
#include "SpellCasterSpawn.h"
#include "BuildingSpawner.generated.h"

UCLASS()
class SHOOTER_API ABuildingSpawner : public ABuilding
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = "Building|Spells", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpellCasterSpawn* SpawnCaster;
	
public:	
	// Sets default values for this actor's properties
	ABuildingSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
