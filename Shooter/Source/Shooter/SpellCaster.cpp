// Fill out your copyright notice in the Description page of Project Settings.

#include "SpellCaster.h"


// Sets default values for this component's properties
USpellCaster::USpellCaster()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	this->CastTime = 0;				// Instant charge cast
	this->CooldownTime = 0;			// Instant cooldown
	this->ChargesCountMax = 1;		// One stack spell
	this->ChargeReloadTime = 5;		// 5 seconds
	this->bIsReloadable = true;		// Can reload charges

}


// Called when the game starts
void USpellCaster::BeginPlay()
{
	Super::BeginPlay();

	this->ChargesCount = this->ChargesCountMax; // Starts the game with every charges

	this->ReloadTimer = this->ReloadTimer;
	this->CastingTimer = 0;
	this->CooldownTimer = 0;
}


// Called every frame
void USpellCaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->bIsReloadable)
	{
		if (this->ChargesCount < this->ChargesCountMax)
		{
			this->ReloadTimer -= DeltaTime;
			if (this->ReloadTimer <= 0)
			{
				this->ReloadTimer += this->ChargeReloadTime;
				this->GetNewCharge();
			}
		}
	}

	if (this->CastingTimer > 0)
	{
		this->CastingTimer -= DeltaTime;
		if (this->CastingTimer <= 0)
		{
			this->OnCastFinished();
		}
	}

	if (this->CooldownTimer > 0)
	{
		this->CooldownTimer -= DeltaTime;
		if (this->CooldownTimer <= 0)
			this->CooldownTimer = 0;
	}
}

void USpellCaster::OnCastFinished()
{
	this->ChargesCount -= 1;
	this->CastingTimer = 0;
	this->CooldownTimer = this->CooldownTime;
	this->DoSpellAction();
}

bool USpellCaster::CanCast()
{
	if (this->CastingTimer > 0)
		return false;

	if (this->ChargesCount == 0)
		return false;

	if (this->CooldownTimer > 0)
		return false;

	return true;
}

void USpellCaster::CastSpell()
{
	if (this->CanCast())
	{
		if (this->CastTime > 0)
		{
			this->CastingTimer = this->CastTime;
		}
		else 
		{
			this->OnCastFinished();
		}
	}
}

void USpellCaster::GetNewCharge()
{
	if (this->ChargesCount < this->ChargesCountMax)
	{
		this->ChargesCount++;
	}

	if (this->ChargesCount == this->ChargesCountMax)
	{
		this->ReloadTimer = this->ChargeReloadTime;
	}
}
