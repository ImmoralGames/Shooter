// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Spell.h"
#include "SpellCaster.generated.h"


UCLASS(BlueprintType, ClassGroup=(Spells))
class SHOOTER_API USpellCaster : public UActorComponent
{
	GENERATED_BODY()

private:

	/** Actual time to wait to get a new charge */
	UPROPERTY(Category = "Spell", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ReloadTimer;

	/** Actual time to wait before the spell effect */
	UPROPERTY(Category = "Spell", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CastingTimer;

	/** Actual time to wait before casting a new time */
	UPROPERTY(Category = "Spell", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CooldownTimer;

	/** Current charges the spell has stacked */
	UPROPERTY(Category = "Spell", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 ChargesCount;
	
	/** Current setted spell */
	UPROPERTY(Category = "Spell", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpell* Spell;

public:	
	// Sets default values for this component's properties
	USpellCaster();

private:
	void GetNewCharge();
	void OnCastFinished();

//protected:
	// Called when the game starts
	//virtual void BeginPlay() override;
	
public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Tells whether the spell is ready or not
	bool CanCast();

	// Called to cast the spell
	void CastSpell();

	// Called to cancel the casting
	void CancelCasting();

	void SetSpell(USpell* spell);
};
