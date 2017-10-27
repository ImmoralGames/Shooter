// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstanceShooter.h"
#include "Shooter.h"



void UGameInstanceShooter::Init()
{
	Super::Init();

	this->TeamUnits = TArray<TArray<APawnShooter*>>();
	for (int32 i = 0; i < TEAM_COUNT; i++)
		this->TeamUnits.Add(TArray<APawnShooter*>());

	this->Enemies = TArray<TArray<APawnShooter*>>();
	for (int32 i = 0; i < TEAM_COUNT; i++)
		this->Enemies.Add(TArray<APawnShooter*>());

	this->Players = TArray<APawnShooter*>();
	this->Monsters = TArray<APawnShooter*>();
	
	APawn* pawn;
	APawnShooter* unit;

	for (FConstPawnIterator itPawn = this->GetWorld()->GetPawnIterator(); itPawn; ++itPawn)
	{
		pawn = itPawn->Get();
		if (pawn == nullptr)
			continue;

		unit = Cast<APawnShooter>(pawn);
		if (unit == nullptr)
			continue;

		this->AddTeamUnit(unit);
	}
}

const TArray<APawnShooter*> UGameInstanceShooter::GetAllies(int32 teamID) const
{
	if (teamID < 0 || teamID >= TEAM_COUNT)
		return TArray<APawnShooter*>();
	return this->TeamUnits[teamID];
}

const TArray<APawnShooter*> UGameInstanceShooter::GetEnemies(int32 teamID) const
{
	if (teamID < 0 || teamID >= TEAM_COUNT)
		return TArray<APawnShooter*>();
	return this->Enemies[teamID];
}


const TArray<APawnShooter*> UGameInstanceShooter::GetPlayers() const
{
	return this->Players;
}

const TArray<APawnShooter*> UGameInstanceShooter::GetMonsters() const
{
	return this->Monsters;
}

void UGameInstanceShooter::AddTeamUnit(APawnShooter* unit)
{
	int32 teamId = unit->GetTeamID();

	this->TeamUnits[teamId].Add(unit);

	if (IS_MONSTER_TEAM(teamId))
		this->Monsters.Add(unit);
	else
		this->Players.Add(unit);

	for (int32 i = 0; i < TEAM_COUNT; i++)
	{
		if (i != teamId)
			this->Enemies[i].Add(unit);
	}
}

void UGameInstanceShooter::RemoveTeamUnit(APawnShooter* unit)
{
	int32 teamId = unit->GetTeamID();

	this->TeamUnits[teamId].Remove(unit);

	if (IS_MONSTER_TEAM(teamId))
		this->Monsters.Remove(unit);
	else
		this->Players.Remove(unit);

	for (int32 i = 0; i < TEAM_COUNT; i++)
	{
		if (i != teamId)
			this->Enemies[i].Remove(unit);
	}
}
