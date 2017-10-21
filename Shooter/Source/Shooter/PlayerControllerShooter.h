// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PawnShip.h"
#include "PawnBuilding.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerShooter.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SHOOTER_API APlayerControllerShooter : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnPossessBuilding(APawnBuilding* building);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnPossessShip(APawnShip* ship);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnPossessGhost(APawnGhost* ghost);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnUnPossess();

	virtual void Possess(APawn* pawn) override;
	virtual void UnPossess() override;

protected:

	void SetupInputComponent() override;
	void RotateShipSin(const float Value);
	void RotateShipCos(const float Value);
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
	void StartShootingBasicWeapon();
	void StopShootingBasicWeapon();
};
