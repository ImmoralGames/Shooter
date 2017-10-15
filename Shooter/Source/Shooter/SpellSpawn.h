// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "PawnShip.h"
#include "SpellSpawn.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Spell), BlueprintType, meta = (BlueprintSpawnableComponent))
class SHOOTER_API USpellSpawn : public USpell
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	USpellSpawn();
	
	UPROPERTY(Category = "Spell|Spawn", EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<APawnShip>> SpawnableShips;
	
protected:
	virtual void Casted_Implementation(AActor* caster) override;
};
