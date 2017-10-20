// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "PawnRotation.generated.h"


UCLASS(Blueprintable, BlueprintType)
class SHOOTER_API UPawnRotation : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPawnRotation();

private:

	FRotator currentRotation;

	FVector2D inputRotation;
	FVector2D inputForward;
	bool ConsumateInputRotationVector(FVector2D& rotation);
	bool ConsumateInputForwardVector(FVector2D& forward);
	

public:	

	UPROPERTY(Category = "PawnShip", EditAnywhere, BlueprintReadWrite)
	float alphaLerp;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	USceneComponent* UpdatedComponent;

	void AddInputRotationVector(const FVector2D & axis);
	void AddInputForwardVector(const FVector2D & axis);
};
