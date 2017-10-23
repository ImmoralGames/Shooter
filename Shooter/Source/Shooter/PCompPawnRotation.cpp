// Fill out your copyright notice in the Description page of Project Settings.

#include "PCompPawnRotation.h"


// Sets default values for this component's properties
UPCompPawnRotation::UPCompPawnRotation() : 
	inputRotation(FVector2D()),
	currentRotation(FRotator())
{
	this->alphaLerp = 10.f;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UPCompPawnRotation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool changed = false;
	
	AActor* owner = this->GetOwner();
	FRotator ownerRotation = owner->GetActorRotation();
	if(ownerRotation != FRotator::ZeroRotator)
	{
		this->currentRotation += ownerRotation;
		owner->SetActorRotation(FRotator::ZeroRotator, ETeleportType::TeleportPhysics);
		changed = true;
	}

	FVector2D rotation;
	if (ConsumateInputRotationVector(rotation))
	{
		if (this->UpdatedComponent != nullptr)
		{
			float angleRad = FMath::Atan2(rotation.Y, rotation.X);
			float angleDegrees = FMath::RadiansToDegrees(angleRad);
			FRotator rotator = FRotator(0, angleDegrees + 90, 0);

			currentRotation = FMath::Lerp(currentRotation, rotator, alphaLerp * DeltaTime);
			changed = true;
		}
	}
	else if (ConsumateInputForwardVector(rotation))
	{
		if (this->UpdatedComponent != nullptr)
		{
			float angleRad = FMath::Atan2(rotation.X, rotation.Y);
			float angleDegrees = FMath::RadiansToDegrees(angleRad);
			FRotator rotator = FRotator(0, -angleDegrees - 90, 0);

			currentRotation = FMath::Lerp(currentRotation, rotator, alphaLerp * DeltaTime);
			changed = true;
		}
	}
	
	if(changed)
		this->UpdatedComponent->SetRelativeRotation(currentRotation);
}

bool UPCompPawnRotation::ConsumateInputRotationVector(FVector2D& rotation)
{
	if (this->inputRotation == FVector2D::ZeroVector)
		return false;

	rotation = this->inputRotation;
	rotation.Normalize();
	this->inputRotation = FVector2D::ZeroVector;

	return true;
}

bool UPCompPawnRotation::ConsumateInputForwardVector(FVector2D& rotation)
{
	if (this->inputForward == FVector2D::ZeroVector)
		return false;

	rotation = this->inputForward;
	rotation.Normalize();
	this->inputForward = FVector2D::ZeroVector;

	return true;
}

void UPCompPawnRotation::AddInputRotationVector(const FVector2D & axis)
{
	this->inputRotation += axis;
}

void UPCompPawnRotation::AddInputForwardVector(const FVector2D & axis)
{
	this->inputForward += axis;
}

