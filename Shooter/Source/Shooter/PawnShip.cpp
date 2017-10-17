// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnShip.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "FloatingPawnMovementShip.h"
#include "Engine.h"
#include "Engine/World.h"
#include "DamageTypeExplosion.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SpellCaster.h"

// Sets default values
APawnShip::APawnShip()
{
	this->MaxHealth = this->Health = 100;
	this->BaseMaxSpeed = 1200;
	this->BaseAcceleration = 4000;
	this->ExplosionDamage = 100;
	this->ExplosionRange = 200;
	this->bCanExplode = false;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent *BaseCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ShipBaseCollision"));
	BaseCollision->InitBoxExtent(FVector(50, 50, 50));
	BaseCollision->CanCharacterStepUpOn = ECB_No;
	
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(BaseCollision);
	SpringArm->RelativeRotation = FRotator(300.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10.0f;
	SpringArm->bDoCollisionTest = false;
	
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	UFloatingPawnMovementShip* FloatingPawnMovementShip = CreateDefaultSubobject<UFloatingPawnMovementShip>(TEXT("ShipMovement"));
	FloatingPawnMovementShip->UpdatedComponent = BaseCollision;

	USpellCaster* spellCasterX = CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterX"));
	USpellCaster* spellCasterY = CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterY"));
	USpellCaster* spellCasterA = CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterA"));
	USpellCaster* spellCasterB = CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterB"));

	this->RootComponent = BaseCollision;
	this->CameraSpringArm = SpringArm;
	this->MovementComponent = FloatingPawnMovementShip;

	this->SpellCasterX = spellCasterX;
	this->SpellCasterY = spellCasterY;
	this->SpellCasterA = spellCasterA;
	this->SpellCasterB = spellCasterB;
	
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

	this->Health = this->MaxHealth;
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

void APawnShip::Explode()
{
	if (this->bCanExplode)
	{
		TArray<AActor*> actorsToIgnore = TArray<AActor*>();
		actorsToIgnore.Add(this);

		bool hasDamagedSomeone = UGameplayStatics::ApplyRadialDamage(this,
			this->ExplosionDamage, this->GetActorLocation(), this->ExplosionRange,
			TSubclassOf<UDamageType>(UDamageTypeExplosion::StaticClass()),
			actorsToIgnore, this, this->GetController(),
			false, ECollisionChannel::ECC_Visibility);

		this->Destroy();
	}
}

TArray<APawnShip*> APawnShip::GetShipsInRange(float range) const
{
	TArray<APawnShip*> retval = TArray<APawnShip*>();

	const UWorld* const world = this->GetWorld();
	if (world == nullptr)
	{
		return retval;
	}
	
	APawn* pawn;
	APawnShip* ship;
	float distance;

	for (FConstPawnIterator itPawn = world->GetPawnIterator(); itPawn; ++itPawn)
	{
		pawn = itPawn->Get();
		if (pawn != nullptr)
		{
			ship = Cast<APawnShip>(pawn);
			if (ship != nullptr && ship->GetController()->IsPlayerController())
			{
				distance = this->GetDistanceTo(ship);

				if (distance < range)
				{
					retval.Add(ship);
				}
			}
		}
	}

	return retval;
}

float APawnShip::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	this->Health -= Damage;
	if (this->Health <= 0)
		this->Destroy();
	
	return Damage;
}

void APawnShip::CastSpellX() { this->SpellCasterX->CastSpell(); }
void APawnShip::CastSpellY() { this->SpellCasterY->CastSpell(); }
void APawnShip::CastSpellA() { this->SpellCasterA->CastSpell(); }
void APawnShip::CastSpellB() { this->SpellCasterB->CastSpell(); }

void APawnShip::CancelSpellX() { this->SpellCasterX->CancelCasting(); }
void APawnShip::CancelSpellY() { this->SpellCasterY->CancelCasting(); }
void APawnShip::CancelSpellA() { this->SpellCasterA->CancelCasting(); }
void APawnShip::CancelSpellB() { this->SpellCasterB->CancelCasting(); }


int32 APawnShip::GetCurrentHealth()
{
	return this->Health;
}

int32 APawnShip::GetMaxHealth()
{
	return this->MaxHealth;
}

float APawnShip::GetPercentHealth()
{
	return (float)this->Health / this->MaxHealth;
}
