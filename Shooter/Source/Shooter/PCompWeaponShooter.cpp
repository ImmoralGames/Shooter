// Fill out your copyright notice in the Description page of Project Settings.

#include "PCompWeaponShooter.h"
#include "Weapon.h"


// Sets default values for this component's properties
UPCompWeaponShooter::UPCompWeaponShooter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UPCompWeaponShooter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->LoadedWeapon != NULL)
	{
		if (this->LoadedWeapon->bIsReloadable)
		{
			if (this->ChargesCount < this->LoadedWeapon->ChargesCountMax)
			{
				this->ReloadTimer -= DeltaTime;
				if (this->ReloadTimer <= 0)
				{
					this->ReloadTimer += this->LoadedWeapon->ChargeReloadTime;
					this->GetNewCharge();
				}
			}
		}

		if (this->ShootingTimer > 0)
		{
			this->ShootingTimer -= DeltaTime;
			if (this->ShootingTimer <= 0)
			{
				this->OnShotFinished();
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

void UPCompWeaponShooter::GetNewCharge() 
{
	if (this->LoadedWeapon != NULL)
	{
		if (this->ChargesCount < this->LoadedWeapon->ChargesCountMax)
		{
			this->ChargesCount++;
		}

		if (this->ChargesCount == this->LoadedWeapon->ChargesCountMax)
		{
			this->ReloadTimer = this->LoadedWeapon->ChargeReloadTime;
		}
	}
}

void UPCompWeaponShooter::OnShotFinished()
{
	this->ChargesCount -= 1;
	this->ShootingTimer = 0;
	this->CooldownTimer = this->LoadedWeapon->CooldownTime;
	this->LoadedWeapon->Shot((APawn*)this->GetOwner(), this);

	if (this->bIsShooting)
		this->ShootAsap();
}	

void UPCompWeaponShooter::StartShooting() 
{
	if(!this->bIsShooting)
	{
		this->bIsShooting = true;
		this->ShootAsap();
	}
}

void UPCompWeaponShooter::StopShooting() 
{
	if(this->bIsShooting)
	{
		this->ShootingTimer = 0;
		this->bIsShooting = false;
	}
}

void UPCompWeaponShooter::ShootAsap()
{
	if(this->ShootingTimer == 0)
		this->ShootingTimer = this->LoadedWeapon->ShootTime;
}

bool UPCompWeaponShooter::HasWeaponLoaded()
{
	return this->LoadedWeapon != NULL;
}

void UPCompWeaponShooter::SetWeapon(TSubclassOf<UWeapon> weaponType) 
{
	UWeapon* weapon = NewObject<UWeapon>((UObject*)GetTransientPackage(), weaponType);
	if (weapon)
		this->SetWeapon(weapon);
}

void UPCompWeaponShooter::SetWeapon(UWeapon* weapon) 
{
	this->LoadedWeapon = weapon;

	this->ChargesCount = this->LoadedWeapon->ChargesCountMax; // Starts the game with every charges
	this->ReloadTimer = this->LoadedWeapon->ChargeReloadTime;
	this->ShootingTimer = 0;
	this->CooldownTimer = 0;
}
	