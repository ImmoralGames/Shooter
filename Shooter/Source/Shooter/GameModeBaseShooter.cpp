// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModeBaseShooter.h"
#include "MyPlayerController.h"

AGameModeBaseShooter::AGameModeBaseShooter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bNetLoadOnClient = false;
	bPauseable = true;
	bStartPlayersAsSpectators = false;

	PlayerControllerClass = AMyPlayerController::StaticClass();

	//DefaultPawnClass = ADefaultPawn::StaticClass();
	//PlayerStateClass = APlayerState::StaticClass();
	//GameStateClass = AGameStateBase::StaticClass();
	//HUDClass = AHUD::StaticClass();
	//GameSessionClass = AGameSession::StaticClass();
	//SpectatorClass = ASpectatorPawn::StaticClass();
	//ReplaySpectatorPlayerControllerClass = APlayerController::StaticClass();
}


