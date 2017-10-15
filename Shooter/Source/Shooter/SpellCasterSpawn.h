// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellCaster.h"
#include "PawnShip.h"
#include "SpellCasterSpawn.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Spell), BlueprintType, meta = (BlueprintSpawnableComponent))
class SHOOTER_API USpellCasterSpawn : public USpellCaster
{
	GENERATED_BODY()
	
protected:
	virtual void DoSpellAction() override;

public:
	// Sets default values for this component's properties
	USpellCasterSpawn();
	
	UPROPERTY(Category = "Spell|Spawn", EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<APawnShip>> SpawnableShips;
};
