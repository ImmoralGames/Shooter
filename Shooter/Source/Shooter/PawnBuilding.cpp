// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnBuilding.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Shooter.h"


// Sets default values
APawnBuilding::APawnBuilding()
{
	UBoxComponent* baseCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BuildingBaseCollision"));
	baseCollision->SetMobility(EComponentMobility::Static);

	this->BaseCollision = baseCollision;
	this->RootComponent = baseCollision;

	this->InitBuildingCollision();
}

void APawnBuilding::InitBuildingCollision()
{
	this->BaseCollision->InitBoxExtent(FVector(500, 500, 500));
	this->BaseCollision->CanCharacterStepUpOn = ECB_No;
	this->BaseCollision->SetCanEverAffectNavigation(false);

	this->BaseCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	this->BaseCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	this->BaseCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
}
