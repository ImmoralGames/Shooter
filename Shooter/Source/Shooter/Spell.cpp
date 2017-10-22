// Fill out your copyright notice in the Description page of Project Settings.

#include "Spell.h"

USpell::USpell()
{
	this->CastTime = 0;				// Instant charge cast
	this->CooldownTime = 0;			// Instant cooldown
	this->ChargesCountMax = 1;		// One stack spell
	this->ChargeReloadTime = 5;		// 5 seconds
	this->bIsReloadable = true;		// Can reload charges
	this->bIsUltimate = false;
	this->bReloadWhenEmpty = false;
}
