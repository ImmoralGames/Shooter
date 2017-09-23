// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnShip.h"
#include "Components/BoxComponent.h"
#include "Components/SkinnedMeshComponent.h"

FName APawnShip::MeshComponentName(TEXT("ShipMesh"));
FName APawnShip::BoxComponentName(TEXT("ShipBaseCollision"));

// Sets default values
APawnShip::APawnShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(APawnShip::BoxComponentName);
	BoxComponent->InitBoxExtent(FVector(1, 1, 1));
	//BoxComponent->InitCapsuleSize(34.0f, 88.0f);
	//BoxComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	BoxComponent->CanCharacterStepUpOn = ECB_No;
	BoxComponent->bShouldUpdatePhysicsVolume = true;
	BoxComponent->bCheckAsyncSceneOnMove = false;
	BoxComponent->SetCanEverAffectNavigation(false);
	BoxComponent->bDynamicObstacle = true;

	RootComponent = BoxComponent;

	Mesh = CreateOptionalDefaultSubobject<USkinnedMeshComponent>(APawnShip::MeshComponentName);
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPose;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetupAttachment(BoxComponent);
		static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->bGenerateOverlapEvents = false;
		Mesh->SetCanEverAffectNavigation(false);
	}
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

// Called to bind functionality to input
void APawnShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

