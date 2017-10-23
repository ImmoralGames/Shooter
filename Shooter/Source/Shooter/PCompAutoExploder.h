// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PCompAutoExploder.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UPCompAutoExploder : public UActorComponent
{
	GENERATED_BODY()
	
private:
	/** Can the pawn explode? */
	UPROPERTY(Category = "AutoExplosion", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bCanExplode;

	/** Explosion's damages */
	UPROPERTY(Category = "AutoExplosion", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionDamage;

	/** Explosion's range */
	UPROPERTY(Category = "AutoExplosion", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ExplosionRange;

public:	
	// Sets default values for this component's properties
	UPCompAutoExploder();
	
public:	
	UFUNCTION(Category = "AutoExplosion", BlueprintCallable, meta = (DefaultToSelf))
	void Explode();
	
};
