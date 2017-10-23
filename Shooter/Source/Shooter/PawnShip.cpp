// Ascii banners made with Bagill's ASCII Signature Generator using the Font: "Small" (width:53)

// ___________________________________________________ //
//           ___         _         _                   //
//          |_ _|_ _  __| |_  _ __| |___ ___           //
//           | || ' \/ _| | || / _` / -_|_-<           //
//          |___|_||_\__|_|\_,_\__,_\___/__/           //
// ___________________________________________________ //

#include "PawnShip.h"
#include "Camera/CameraComponent.h"
#include "WeaponMiniShootingGun.h"
#include "Shooter.h"

// ___________________________________________________ //
//    ___             _               _                //
//   / __|___ _ _  __| |_ _ _ _  _ __| |_ ___ _ _ ___  //
//  | (__/ _ \ ' \(_-<  _| '_| || / _|  _/ _ \ '_(_-<  //
//   \___\___/_||_/__/\__|_|  \_,_\__|\__\___/_| /__/  //
// ___________________________________________________ //

APawnShip::APawnShip()
{
	this->BaseMaxSpeed = 4000;
	this->BaseAcceleration = 8000;
	this->BaseDeceleration = 8000;
	this->bIsAutomaticallyLookingAtMovementDirection = false;
	
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(this->RootComponent);
	SpringArm->RelativeRotation = FRotator(300.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 9000.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10.0f;
	SpringArm->bDoCollisionTest = false;
	
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	USceneComponent* pivot = CreateDefaultSubobject<USceneComponent>(TEXT("RotationPivot"));
	pivot->SetupAttachment(this->RootComponent);

	UStaticMeshComponent* model = CreateDefaultSubobject<UStaticMeshComponent>("Model");
	model->SetupAttachment(pivot);
	model->RelativeLocation = FVector(0, 0, -150);

	UFloatingPawnMovement* FloatingPawnMovementShip = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("ShipMovement"));
	FloatingPawnMovementShip->UpdatedComponent = this->RootComponent;

	UPCompPawnRotation* rotationComponent = CreateDefaultSubobject<UPCompPawnRotation>(TEXT("ShipRotation"));
	rotationComponent->UpdatedComponent = pivot;
	
	UPCompSpellCaster* spellCasterY		= CreateDefaultSubobject<UPCompSpellCaster>(TEXT("SpellCasterY"));
	spellCasterY->SetupAttachment(pivot);

	UPCompSpellCaster* spellCasterX		= CreateDefaultSubobject<UPCompSpellCaster>(TEXT("SpellCasterX"));
	spellCasterX->SetupAttachment(pivot);

	UPCompSpellCaster* spellCasterA		= CreateDefaultSubobject<UPCompSpellCaster>(TEXT("SpellCasterA"));
	spellCasterA->SetupAttachment(pivot);

	UPCompSpellCaster* spellCasterB		= CreateDefaultSubobject<UPCompSpellCaster>(TEXT("SpellCasterB"));
	spellCasterB->SetupAttachment(pivot);

	UPCompWeaponShooter* basicWeaponShooter	= CreateDefaultSubobject<UPCompWeaponShooter>(TEXT("WeaponShooterBasic"));
	basicWeaponShooter->SetupAttachment(pivot);
	basicWeaponShooter->SetWeapon(UWeaponMiniShootingGun::StaticClass());

	this->ModelComponent = model;
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
	this->BaseCollision->SetConstraintMode(EDOFMode::XYPlane);
	
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
//             ___      _   _                          //
//            / __| ___| |_| |_ ___ _ _ ___            //
//            \__ \/ -_)  _|  _/ -_) '_(_-<            //
//            |___/\___|\__|\__\___|_| /__/            //
// ___________________________________________________ //

void APawnShip::SetIsAutomaticallyLookingAtDirection(bool enable)
{
	this->bIsAutomaticallyLookingAtMovementDirection = enable;
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

	this->MovementComponent->Deceleration	= this->BaseDeceleration;
	this->MovementComponent->Acceleration	= this->BaseAcceleration;
	this->MovementComponent->MaxSpeed		= this->BaseMaxSpeed;
}

void APawnShip::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	FVector Location = this->GetActorLocation();
	if (Location.Z != 500)
	{
		Location.Z = 500;
		this->SetActorLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
	}
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

void APawnShip::AddInputVector(const FVector & direction) 
{
	this->MovementComponent->AddInputVector(direction);
}

void APawnShip::AddInputRotationVector(const FVector2D & axis) 
{
	this->RotationComponent->AddInputRotationVector(axis);
}

void APawnShip::AddInputForwardVector(const FVector2D & axis) 
{
	this->RotationComponent->AddInputForwardVector(axis);
}

void APawnShip::LookAt(const FVector& position)
{
	this->LookAtDirection(this->GetActorLocation() - position);
}

void APawnShip::LookAtDirection(FVector direction)
{
	direction.Normalize();
	this->LookAtDirectionNormalized(direction);
}

void APawnShip::LookAtDirectionNormalized(const FVector& direction)
{
	this->RotationComponent->AddInputForwardVector(FVector2D(direction.X, direction.Y));
}

void APawnShip::GoTowardPosition(const FVector& position)
{
	FVector direction = position - this->GetActorLocation();
	direction.Normalize();
	this->MovementComponent->AddInputVector(direction);
	
	if(this->bIsAutomaticallyLookingAtMovementDirection)
		this->LookAtDirectionNormalized(-direction);
}

void APawnShip::GoFromPosition(const FVector& position)
{
	FVector direction = this->GetActorLocation() - position;
	direction.Normalize();
	this->MovementComponent->AddInputVector(direction);
	
	if(this->bIsAutomaticallyLookingAtMovementDirection)
		this->LookAtDirectionNormalized(-direction);
}
