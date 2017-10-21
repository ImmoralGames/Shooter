// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnGhost.h"
#include "Camera/CameraComponent.h"


APawnGhost::APawnGhost()
{
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(this->RootComponent);
	SpringArm->RelativeRotation = FRotator(300.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 9000.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10.0f;
	SpringArm->bDoCollisionTest = false;

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	this->MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("GhostMovement"));
	this->MovementComponent->UpdatedComponent = this->RootComponent;

	this->MovementComponent->Acceleration = 8000;
	this->MovementComponent->MaxSpeed = 4000;
}

void APawnGhost::InitResurrection(float timer, TSubclassOf<APawnShooter> type)
{
	this->ResurrectType = type;
	this->TimeBeforeResurrection = timer;
	this->ResurrectionTimer = timer;
}

void APawnGhost::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	if (this->ResurrectionTimer > 0)
	{
		this->ResurrectionTimer -= DeltaTime;
		if (this->ResurrectionTimer <= 0)
		{
			this->Resurrect();
		}
	}
}

void APawnGhost::Resurrect() 
{	
	AController* controller = this->GetController();
	if (controller != nullptr && controller->IsPlayerController())
	{
		APawnShooter* pawn = this->GetWorld()->SpawnActor<APawnShooter>(this->ResurrectType);
		
		controller->UnPossess();
		controller->Possess(pawn);
	}

	this->Destroy();
}

void APawnGhost::AddInputVector(const FVector & input) const 
{
	this->MovementComponent->AddInputVector(input);
}