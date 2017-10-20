// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnRotation.h"


// Sets default values for this component's properties
UPawnRotation::UPawnRotation() : 
	inputRotation(FVector2D()),
	currentRotation(FRotator())
{
	this->alphaLerp = 10.f;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame
void UPawnRotation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector2D rotation;
	if (ConsumateInputRotationVector(rotation))
	{
		if (this->UpdatedComponent != nullptr)
		{
			float angleRad = FMath::Atan2(rotation.Y, rotation.X);
			float angleDegrees = FMath::RadiansToDegrees(angleRad);
			FRotator rotator = FRotator(0, angleDegrees + 90, 0);

			currentRotation = FMath::Lerp(currentRotation, rotator, alphaLerp * DeltaTime);

			this->UpdatedComponent->SetRelativeRotation(currentRotation);
		}
	}
	else if (ConsumateInputForwardVector(rotation))
	{
		if (this->UpdatedComponent != nullptr)
		{
			float angleRad = FMath::Atan2(rotation.X, rotation.Y);
			float angleDegrees = FMath::RadiansToDegrees(angleRad);
			FRotator rotator = FRotator(0, -angleDegrees + 90, 0);

			currentRotation = FMath::Lerp(currentRotation, rotator, alphaLerp * DeltaTime);

			this->UpdatedComponent->SetRelativeRotation(currentRotation);
		}
	}
}

bool UPawnRotation::ConsumateInputRotationVector(FVector2D& rotation)
{
	if (this->inputRotation == FVector2D::ZeroVector)
		return false;

	rotation = this->inputRotation;
	rotation.Normalize();
	this->inputRotation = FVector2D::ZeroVector;

	return true;
}

bool UPawnRotation::ConsumateInputForwardVector(FVector2D& rotation)
{
	if (this->inputForward == FVector2D::ZeroVector)
		return false;

	rotation = this->inputForward;
	rotation.Normalize();
	this->inputForward = FVector2D::ZeroVector;

	return true;
}

void UPawnRotation::AddInputRotationVector(const FVector2D & axis)
{
	this->inputRotation += axis;
}

void UPawnRotation::AddInputForwardVector(const FVector2D & axis)
{
	this->inputForward += axis;
}

