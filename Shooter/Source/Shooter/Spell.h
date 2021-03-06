// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/Texture2D.h"
#include "Runtime/Engine/Classes/Engine/DataAsset.h"
#include "Spell.generated.h"

/**
 * 
 */
UCLASS(abstract, Blueprintable, BlueprintType, ClassGroup = (Spells))
class SHOOTER_API USpell : public UDataAsset
{
	GENERATED_BODY()

public:

	/** Time to wait to have a new charge */
	UPROPERTY(Category = "Spell", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ChargeReloadTime;

	/** Time to wait after casting the spell for the spell action to start */
	UPROPERTY(Category = "Spell", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CastTime;

	/** Time to wait after a spell action before casting a new time */
	UPROPERTY(Category = "Spell", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CooldownTime;

	/** Max charges the spell can stack */
	UPROPERTY(Category = "Spell", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 ChargesCountMax;

	/** Tells whether the spell can reload its stack or not */
	UPROPERTY(Category = "Spell", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsReloadable;
	
	/** Tells whether the spell can reload its stack or not only if empty */
	UPROPERTY(Category = "Spell", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bReloadWhenEmpty;

	/** Tells whether the spell can reload its stack or not */
	UPROPERTY(Category = "Spell", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsUltimate;

	/** UI: Texture for the spell button */
	UPROPERTY(Category = "Spell", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UTexture2D* SpellImage;
	
protected:
	USpell();

	UFUNCTION(BlueprintCallable, Category = "Spell")
	virtual void Casted_Implementation(APawn* caster, USceneComponent* castingComponent) PURE_VIRTUAL(USpell::Casted_Implementation, );

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Spell")
	void Casted(APawn* caster, USceneComponent* castingComponent);

};
