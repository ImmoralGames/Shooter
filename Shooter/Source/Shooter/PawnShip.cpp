// Ascii banners made with Bagill's ASCII Signature Generator using the Font: "Small" (width:53)

// ___________________________________________________ //
//           ___         _         _                   //
//          |_ _|_ _  __| |_  _ __| |___ ___           //
//           | || ' \/ _| | || / _` / -_|_-<           //
//          |___|_||_\__|_|\_,_\__,_\___/__/           //
// ___________________________________________________ //

#include "PawnShip.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PawnRotation.h"
#include "Camera/CameraComponent.h"
#include "FloatingPawnMovementShip.h"
#include "SpellCaster.h"
#include "WeaponShooter.h"
#include "WeaponMiniShootingGun.h"
#include "Shooter.h"

// ___________________________________________________ //
//   ___             _               _                 //
//  / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _ ___   //
// | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_(_-<   //
//  \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_| /__/   //
// ___________________________________________________ //

APawnShip::APawnShip()
{
	this->BaseMaxSpeed = 4000;
	this->BaseAcceleration = 8000;

	UBoxComponent* baseCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ShipBaseCollision"));

	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(baseCollision);
	SpringArm->RelativeRotation = FRotator(320.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 3500.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10.0f;
	SpringArm->bDoCollisionTest = false;
	
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	USceneComponent* pivot = CreateDefaultSubobject<UBoxComponent>(TEXT("RotationPivot"));
	pivot->SetupAttachment(baseCollision);

	UStaticMeshComponent* model = CreateDefaultSubobject<UStaticMeshComponent>("Model");
	model->SetupAttachment(pivot);
	model->RelativeLocation = FVector(0, 0, -150);

	UFloatingPawnMovementShip* FloatingPawnMovementShip = CreateDefaultSubobject<UFloatingPawnMovementShip>(TEXT("ShipMovement"));
	FloatingPawnMovementShip->UpdatedComponent = baseCollision;

	UPawnRotation* rotationComponent = CreateDefaultSubobject<UPawnRotation>(TEXT("ShipRotation"));
	rotationComponent->UpdatedComponent = pivot;
	
	USpellCaster* spellCasterY		= CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterY"));
	spellCasterY->SetupAttachment(pivot);

	USpellCaster* spellCasterX		= CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterX"));
	spellCasterX->SetupAttachment(pivot);

	USpellCaster* spellCasterA		= CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterA"));
	spellCasterA->SetupAttachment(pivot);

	USpellCaster* spellCasterB		= CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterB"));
	spellCasterB->SetupAttachment(pivot);

	UWeaponShooter* basicWeaponShooter	= CreateDefaultSubobject<UWeaponShooter>(TEXT("WeaponShooterBasic"));
	basicWeaponShooter->SetupAttachment(pivot);
	basicWeaponShooter->SetWeapon(UWeaponMiniShootingGun::StaticClass());

	this->RootComponent = baseCollision;
	this->ModelComponent = model;
	this->BaseCollision = baseCollision;
	this->CameraSpringArm = SpringArm;
	this->MovementComponent = FloatingPawnMovementShip;
	this->RotationComponent = rotationComponent;

	this->SpellCasterX = spellCasterX;
	this->SpellCasterY = spellCasterY;
	this->SpellCasterA = spellCasterA;
	this->SpellCasterB = spellCasterB;

	this->BasicWeaponShooter = basicWeaponShooter;
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;

	//Mesh = CreateDefaultSubobject<UMeshComponent>(TEXT("ShipMesh"));
	//if (Mesh)
	//{
	//	Mesh->SetupAttachment(BaseCollision);
	//	Mesh->SetCollisionProfileName(TEXT("Pawn"));
	//}
	
	this->InitShipCollision();
}

// ___________________________________________________ //
//       ___      _ _   _      _ _                     //
//      |_ _|_ _ (_) |_(_)__ _| (_)______ _ _ ___      //
//       | || ' \| |  _| / _` | | |_ / -_) '_(_-<      //
//      |___|_||_|_|\__|_\__,_|_|_/__\___|_| /__/      //
// ___________________________________________________ //

void APawnShip::InitShipCollision()
{	
	this->BaseCollision->InitBoxExtent(FVector(300, 150, 150));
	this->BaseCollision->CanCharacterStepUpOn = ECB_No;

	this->BaseCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	this->BaseCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	this->BaseCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);

	this->ModelComponent->bGenerateOverlapEvents = false;
	this->ModelComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	this->ModelComponent->CanCharacterStepUpOn = ECB_No;
}


// ___________________________________________________ //
//              ___             _                      //
//             | __|_ _____ _ _| |_ ___                //
//             | _|\ V / -_) ' \  _(_-<                //
//             |___|\_/\___|_||_\__/__/                //
// ___________________________________________________ //

void APawnShip::BeginPlay()
{
	Super::BeginPlay();

	if(!this->BasicWeaponShooter->HasWeaponLoaded())
		this->BasicWeaponShooter->SetWeapon(UWeaponMiniShootingGun::StaticClass());

	this->MovementComponent->Acceleration	= this->BaseAcceleration;
	this->MovementComponent->MaxSpeed		= this->BaseMaxSpeed;
}

// ___________________________________________________ //
//        ___                              _           //
//       / __|___ _ __  _ __  __ _ _ _  __| |___       //
//      | (__/ _ \ '  \| '  \/ _` | ' \/ _` (_-<       //
//       \___\___/_|_|_|_|_|_\__,_|_||_\__,_/__/       //
// ___________________________________________________ //



void APawnShip::CastSpellX() { 
	this->SpellCasterX->CastSpell(); 
}

void APawnShip::CastSpellY() { 
	this->SpellCasterY->CastSpell(); 
}

void APawnShip::CastSpellA() { 
	this->SpellCasterA->CastSpell(); 
}

void APawnShip::CastSpellB() { 
	this->SpellCasterB->CastSpell(); 
}

void APawnShip::CancelSpellX() { 
	this->SpellCasterX->CancelCasting(); 
}

void APawnShip::CancelSpellY() { 
	this->SpellCasterY->CancelCasting(); 
}

void APawnShip::CancelSpellA() {
	this->SpellCasterA->CancelCasting(); 
}

void APawnShip::CancelSpellB() { 
	this->SpellCasterB->CancelCasting(); 
}

void APawnShip::ShootBasicWeapon()
{
	this->BasicWeaponShooter->ShootAsap();
}

void APawnShip::StartShootingBasicWeapon()
{
	this->BasicWeaponShooter->StartShooting();
}

void APawnShip::StopShootingBasicWeapon()
{
	this->BasicWeaponShooter->StopShooting();
}

void APawnShip::AddInputVector(const FVector & direction) const
{
	this->MovementComponent->AddInputVector(direction);
}

void APawnShip::AddInputRotationVector(const FVector2D & axis) const
{
	this->RotationComponent->AddInputRotationVector(axis);
}
