// Ascii banners made with Bagill's ASCII Signature Generator using the Font: "Small" (width:53)

// ___________________________________________________ //
//           ___         _         _                   //
//          |_ _|_ _  __| |_  _ __| |___ ___           //
//           | || ' \/ _| | || / _` / -_|_-<           //
//          |___|_||_\__|_|\_,_\__,_\___/__/           //
// ___________________________________________________ //

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
	this->MaxHealth = this->Health = 100;
	this->BaseMaxSpeed = 1200;
	this->BaseAcceleration = 4000;
	this->ExplosionDamage = 100;
	this->ExplosionRange = 200;
	this->bCanExplode = false;
	
	this->TeamID = MONSTER_TEAM;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent *baseCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ShipBaseCollision"));
	
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(baseCollision);
	SpringArm->RelativeRotation = FRotator(300.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10.0f;
	SpringArm->bDoCollisionTest = false;
	
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	UFloatingPawnMovementShip* FloatingPawnMovementShip = CreateDefaultSubobject<UFloatingPawnMovementShip>(TEXT("ShipMovement"));
	FloatingPawnMovementShip->UpdatedComponent = baseCollision;
	
	USpellCaster* spellCasterY		= CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterY"));
	USpellCaster* spellCasterX		= CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterX"));
	USpellCaster* spellCasterA		= CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterA"));
	USpellCaster* spellCasterB		= CreateDefaultSubobject<USpellCaster>(TEXT("SpellCasterB"));

	UWeaponShooter* basicWeaponShooter	= CreateDefaultSubobject<UWeaponShooter>(TEXT("WeaponShooterBasic"));
	basicWeaponShooter->SetWeapon(UWeaponMiniShootingGun::StaticClass());

	this->RootComponent = baseCollision;
	this->BaseCollision = baseCollision;
	this->CameraSpringArm = SpringArm;
	this->MovementComponent = FloatingPawnMovementShip;

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

void APawnShip::InitShipCollision()
{	
	this->BaseCollision->InitBoxExtent(FVector(50, 50, 50));
	this->BaseCollision->CanCharacterStepUpOn = ECB_No;

	this->BaseCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	this->BaseCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	this->BaseCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	this->BaseCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
}

// ___________________________________________________ //
//              ___     _   _                          //
//             / __|___| |_| |_ ___ _ _ ___            //
//            | (_ / -_)  _|  _/ -_) '_(_-<            //
//             \___\___|\__|\__\___|_| /__/            //
// ___________________________________________________ //

int32 APawnShip::GetCurrentHealth() const
{
	return this->Health;
}

int32 APawnShip::GetMaxHealth() const
{
	return this->MaxHealth;
}

float APawnShip::GetPercentHealth() const
{
	return (float)this->Health / this->MaxHealth;
}

int32 APawnShip::GetTeamID() const 
{
	return this->TeamID;
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

// ___________________________________________________ //
//             ___      _   _                          //
//            / __| ___| |_| |_ ___ _ _ ___            //
//            \__ \/ -_)  _|  _/ -_) '_(_-<            //
//            |___/\___|\__|\__\___|_| /__/            //
// ___________________________________________________ //

void APawnShip::SetTeamID(int32 teamID)
{
	this->TeamID = teamID;
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

	this->Health = this->MaxHealth;
	this->MovementComponent->Acceleration	= this->BaseAcceleration;
	this->MovementComponent->MaxSpeed		= this->BaseMaxSpeed;
}

void APawnShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

float APawnShip::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	this->Health -= Damage;
	if (this->Health <= 0)
		this->Destroy();

	return Damage;
}

// ___________________________________________________ //
//               _      _   _                          //
//              /_\  __| |_(_)___ _ _  ___             //
//             / _ \/ _|  _| / _ \ ' \(_-<             //
//            /_/ \_\__|\__|_\___/_||_/__/             //
// ___________________________________________________ //

// ___________________________________________________ //
//        ___                              _           //
//       / __|___ _ __  _ __  __ _ _ _  __| |___       //
//      | (__/ _ \ '  \| '  \/ _` | ' \/ _` (_-<       //
//       \___\___/_|_|_|_|_|_\__,_|_||_\__,_/__/       //
// ___________________________________________________ //

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