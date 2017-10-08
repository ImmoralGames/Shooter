// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnShip.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "FloatingPawnMovementShip.h"


// Sets default values
APawnShip::APawnShip()
{
	this->BaseMaxSpeed = 1200;
	this->BaseAcceleration = 4000;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent *BaseCollision;
	RootComponent = BaseCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ShipBaseCollision"));
	BaseCollision->InitBoxExtent(FVector(50, 50, 50));
	BaseCollision->CanCharacterStepUpOn = ECB_No;
	
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = FRotator(-90.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10.0f;
	SpringArm->bDoCollisionTest = false;
	
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	this->MovementComponent = CreateDefaultSubobject<UFloatingPawnMovementShip>(TEXT("ShipMovement"));
	this->MovementComponent->UpdatedComponent = RootComponent;
	
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Mesh = CreateDefaultSubobject<UMeshComponent>(TEXT("ShipMesh"));
	//if (Mesh)
	//{
	//	Mesh->SetupAttachment(BaseCollision);
	//	Mesh->SetCollisionProfileName(TEXT("Pawn"));
	//}
}

// Called when the game starts or when spawned
void APawnShip::BeginPlay()
{
	Super::BeginPlay();
	this->MovementComponent->Acceleration	= this->BaseAcceleration;
	this->MovementComponent->MaxSpeed		= this->BaseMaxSpeed;
}

// Called every frame
void APawnShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called by script or blueprint to move the ship
void APawnShip::AddInputVector(const FVector & direction) const
{
	this->MovementComponent->AddInputVector(direction);
}