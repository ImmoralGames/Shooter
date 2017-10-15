// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpellCaster.generated.h"


UCLASS(abstract, BlueprintType, ClassGroup=(Spells))
class SHOOTER_API USpellCaster : public UActorComponent
{
	GENERATED_BODY()

private:

	/** Actual time to wait to get a new charge */
	UPROPERTY(Category = "Spell|stats", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ReloadTimer;

	/** Actual time to wait before the spell effect */
	UPROPERTY(Category = "Spell|stats", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CastingTimer;

	/** Actual time to wait before casting a new time */
	UPROPERTY(Category = "Spell|stats", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CooldownTimer;

	/** Current charges the spell has stacked */
	UPROPERTY(Category = "Spell|stats", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 ChargesCount;

private:

	/** Time to wait to have a new charge */
	UPROPERTY(Category = "Spell|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ChargeReloadTime;

	/** Time to wait after casting the spell for the spell action to start */
	UPROPERTY(Category = "Spell|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CastTime;

	/** Time to wait after a spell action before casting a new time */
	UPROPERTY(Category = "Spell|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CooldownTime;

	/** Max charges the spell can stack */
	UPROPERTY(Category = "Spell|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 ChargesCountMax;

	/** Tells whether the spell can reload its stack or not */
	UPROPERTY(Category = "Spell|stats", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsReloadable;

protected:	
	// Sets default values for this component's properties
	USpellCaster();

private:
	void GetNewCharge();
	void OnCastFinished();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void DoSpellAction() PURE_VIRTUAL(USpellCaster::DoSpellAction, )
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Tells whether the spell is ready or not
	virtual bool CanCast();

	// Called to cast the spell
	virtual void CastSpell();
};
