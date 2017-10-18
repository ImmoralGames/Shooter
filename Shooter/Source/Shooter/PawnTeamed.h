// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnTeamed.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta=(CannotImplementInterfaceInBlueprint)) // for now, not implementable in blueprints. Later maybe.
class UPawnTeamed : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SHOOTER_API IPawnTeamed
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:

	virtual int32 GetTeamID() const = 0;
	virtual void SetTeamID(int32 teamID) = 0;
	
};
