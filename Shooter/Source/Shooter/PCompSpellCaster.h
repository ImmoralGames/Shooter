// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Spell.h"
#include "PCompSpellCaster.generated.h"


UCLASS(BlueprintType, ClassGroup=(Spells))
class SHOOTER_API UPCompSpellCaster : public USceneComponent
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
	UPCompSpellCaster();

private:
	void GetFullCharge();
	void GetNewCharge();
	void OnCastFinished();
	void InitStats();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Tells whether the spell is ready or not
	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool CanCast() const;

	// Called to cast the spell
	UFUNCTION(BlueprintCallable)
	void CastSpell();

	// Called to cancel the casting
	UFUNCTION(BlueprintCallable)
	void CancelCasting();

	UFUNCTION(BlueprintCallable)
	void SetSpell(USpell* newSpell);

	UFUNCTION(BlueprintCallable)
	void SetSpellType(TSubclassOf<USpell> newSpellType);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool HasSpellSetted() const;
};
