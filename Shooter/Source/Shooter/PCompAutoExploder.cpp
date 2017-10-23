// Fill out your copyright notice in the Description page of Project Settings.

#include "PCompAutoExploder.h"
#include "DamageTypeExplosion.h"
#include "PawnShooter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UPCompAutoExploder::UPCompAutoExploder()
{
	//PrimaryComponentTick.bCanEverTick = true;

	this->ExplosionDamage = 100;
	this->ExplosionRange = 1000;
	this->bCanExplode = false;
}


void UPCompAutoExploder::Explode()
{
	if (this->bCanExplode)
	{
		APawnShooter* owner = (APawnShooter*)this->GetOwner();
		
		TArray<AActor*> actorsToIgnore = TArray<AActor*>();
		actorsToIgnore.Add(owner);

		bool hasDamagedSomeone = UGameplayStatics::ApplyRadialDamage(this,
			this->ExplosionDamage, owner->GetActorLocation(), this->ExplosionRange,
			TSubclassOf<UDamageType>(UDamageTypeExplosion::StaticClass()),
			actorsToIgnore, owner, NULL,
			false, ECollisionChannel::ECC_Visibility);

		owner->Dead();
	}
}
