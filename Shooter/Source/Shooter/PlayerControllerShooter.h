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

private:
	FVector2D LastMousePosition;
	bool bIsMouseLastDetected;

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnPossessBuilding(APawnBuilding* building);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnPossessShip(APawnShip* ship);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnPossessGhost(APawnGhost* ghost);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnUnPossess();

	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void Possess(APawn* pawn) override;
	virtual void UnPossess() override;
	
private:
	void ManageMouse();
	void ManageShipMouseRotation(APawnShip* ownedShip);

protected:
	void SetupInputComponent() override;
	void RotatePawnSin(const float Value);
	void RotatePawnCos(const float Value);
	void MovePawnForward(const float Value);
	void MovePawnRight(const float Value);
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
	void EnableGodMode();
	void DisableGodMode();
};
