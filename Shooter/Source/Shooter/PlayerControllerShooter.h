// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerShooter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API APlayerControllerShooter : public APlayerController
{
	GENERATED_BODY()
			
protected:

	void SetupInputComponent() override;
	void MoveShipForward(const float Value);
	void MoveShipRight(const float Value);
	void CastSpellX();
	void CastSpellY();
	void CastSpellA();
	void CastSpellB();
	void CancelSpellX();
	void CancelSpellY();
	void CancelSpellA();
	void CancelSpellB();
};
