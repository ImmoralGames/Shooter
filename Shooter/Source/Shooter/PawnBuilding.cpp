// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnBuilding.h"


// Sets default values
APawnBuilding::APawnBuilding()
{
	this->InitBuildingCollision();
}

void APawnBuilding::InitBuildingCollision()
{
	this->BaseCollision->SetMobility(EComponentMobility::Static);

	this->BaseCollision->InitBoxExtent(FVector(500, 500, 500));
	this->BaseCollision->CanCharacterStepUpOn = ECB_No;
	this->BaseCollision->SetCanEverAffectNavigation(false);

	this->BaseCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	this->BaseCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	this->BaseCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
}

void APawnBuilding::AddInputVector(const FVector& input)
{

}

void APawnBuilding::LookAt(const FVector& position)
{

}

void APawnBuilding::AddInputRotationVector(const FVector2D& input)
{

}

void APawnBuilding::AddInputForwardVector(const FVector2D& input)
{

}