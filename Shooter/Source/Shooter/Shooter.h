// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Monster teams
const int32 MONSTER_TEAM = 0; // default monster team
const int32 MONSTER_TEAM_1 = 0;
const int32 MONSTER_TEAM_2 = 2;

// Player teams
const int32 PLAYER_TEAM_1 = 1;
const int32 PLAYER_TEAM_2 = 3;

#define IS_MONSTER_TEAM(x) (((x)%2)==0)
#define MUST_LOG_HITS (false)