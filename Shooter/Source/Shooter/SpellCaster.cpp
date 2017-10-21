// Fill out your copyright notice in the Description page of Project Settings.

#include "SpellCaster.h"
#include "Spell.h"


// Sets default values for this component's properties
USpellCaster::USpellCaster()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}

void USpellCaster::BeginPlay()
{
	Super::BeginPlay();
	this->InitStats();
}

void USpellCaster::InitStats()
{
	if (this->Spell != nullptr)
	{
		this->ChargesCount = this->Spell->ChargesCountMax; // Starts the game with every charges
		this->ReloadTimer = this->Spell->ChargeReloadTime;
		this->CastingTimer = 0;
		this->CooldownTimer = 0;
	}
}

void USpellCaster::SetSpell(USpell* spell)
{
	this->Spell = spell;
	this->InitStats();
}


void USpellCaster::SetSpellType(TSubclassOf<USpell> spellType)
{
	USpell* spell = NewObject<USpell>((UObject*)GetTransientPackage(), spellType);
	if(spell)
		this->SetSpell(spell);
}

// Called every frame
void USpellCaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->Spell != NULL)
	{
		if (this->Spell->bIsReloadable)
		{
			if (this->ChargesCount < this->Spell->ChargesCountMax)
			{
				this->ReloadTimer -= DeltaTime;
				if (this->ReloadTimer <= 0)
				{
					this->ReloadTimer += this->Spell->ChargeReloadTime;
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
}

bool USpellCaster::HasSpellSetted() const
{
	return this->Spell != nullptr;
}

void USpellCaster::OnCastFinished()
{
	this->ChargesCount -= 1;
	this->CastingTimer = 0;
	this->CooldownTimer = this->Spell->CooldownTime;
	this->Spell->Casted((APawn*)this->GetOwner(), this);
}

bool USpellCaster::CanCast() const
{
	if (this->Spell == NULL)
		return false;

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
		if (this->CastingTimer > 0)
		{
			this->CastingTimer = this->Spell->CastTime;
		}
		else 
		{
			this->OnCastFinished();
		}
	}
}

void USpellCaster::CancelCasting() 
{
	this->CastingTimer = 0;
}

void USpellCaster::GetNewCharge()
{
	if (this->Spell != NULL)
	{
		if (this->ChargesCount < this->Spell->ChargesCountMax)
		{
			this->ChargesCount++;
		}

		if (this->ChargesCount == this->Spell->ChargesCountMax)
		{
			this->ReloadTimer = this->Spell->ChargeReloadTime;
		}
	}
}
