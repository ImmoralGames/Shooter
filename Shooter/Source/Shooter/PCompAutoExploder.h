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
	
	/** Tells whether the projectile can damage allies */
	UPROPERTY(Category = "AutoExplosion", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireShips;

	/** Tells whether the projectile can damage allied buildings */
	UPROPERTY(Category = "AutoExplosion", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireBuilding;

	/** Tells whether the projectile can damage allies IF in monster team */
	UPROPERTY(Category = "AutoExplosion", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireShipsMonster;

	/** Tells whether the projectile can damage allied buildings IF in monster team*/
	UPROPERTY(Category = "AutoExplosion", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bFriendlyFireBuildingMonster;

public:	
	// Sets default values for this component's properties
	UPCompAutoExploder();
	
public:	
	UFUNCTION(Category = "AutoExplosion", BlueprintCallable, meta = (DefaultToSelf))
	void Explode();
	
};
