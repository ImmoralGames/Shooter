// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageTypeBulletImpact.h"

UDamageTypeBulletImpact::UDamageTypeBulletImpact()
{
	this->bCausedByWorld = false;
	this->bRadialDamageVelChange = false;
	this->bScaleMomentumByMass = false;
	this->DamageFalloff = 0;
	this->DamageImpulse = 0;
	this->DestructibleDamageSpreadScale = 0;
	this->DestructibleImpulse = 0;
}

