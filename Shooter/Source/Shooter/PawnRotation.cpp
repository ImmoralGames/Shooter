// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnRotation.h"


// Sets default values for this component's properties
UPawnRotation::UPawnRotation() : 
	targetRotation(FVector2D())
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame
void UPawnRotation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector2D rotation;
	if (ConsumateRotationVector(rotation))
	{
		if (this->UpdatedComponent != nullptr)
		{
			float angleRad = FMath::Atan2(rotation.Y, rotation.X);
			float angleDegrees = FMath::RadiansToDegrees(angleRad) + 90;
			FRotator rotator = FRotator(0, angleDegrees, 0);
			this->UpdatedComponent->SetRelativeRotation(rotator);
		}
	}
}

bool UPawnRotation::ConsumateRotationVector(FVector2D& rotation)
{
	if (this->targetRotation == FVector2D::ZeroVector)
		return false;

	rotation = this->targetRotation;
	rotation.Normalize();
	this->targetRotation = FVector2D::ZeroVector;

	return true;
}

void UPawnRotation::AddInputRotationVector(const FVector2D & axis)
{
	this->targetRotation += axis;
}