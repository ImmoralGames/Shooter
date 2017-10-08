// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnShip.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "FloatingPawnMovementShip.h"


// Sets default values
APawnShip::APawnShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent *BaseCollision;
	RootComponent = BaseCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ShipBaseCollision"));
	BaseCollision->InitBoxExtent(FVector(50, 50, 50));
	BaseCollision->CanCharacterStepUpOn = ECB_No;
	

	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	this->MovementComponent = CreateDefaultSubobject<UFloatingPawnMovementShip>(TEXT("ShipMovement"));
	this->MovementComponent->UpdatedComponent = RootComponent;

	this->MovementComponent->Acceleration		= this->BaseAcceleration;
	this->MovementComponent->MaxSpeed			= this->BaseMaxSpeed;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

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