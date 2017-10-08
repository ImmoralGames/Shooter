// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageTypeShipExplosion.h"

UDamageTypeShipExplosion::UDamageTypeShipExplosion()
{
	this->bCausedByWorld = false;
	this->bRadialDamageVelChange = false;
	this->bScaleMomentumByMass = false;
	this->DamageFalloff = 1.0f;
	this->DamageImpulse = 10;
	this->DestructibleDamageSpreadScale = 1;
	this->DestructibleImpulse = 1;
}


