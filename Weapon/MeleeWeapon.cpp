// // @2023 All rights reversed by Reverse-Alpha Studios

#include "MeleeWeapon.h"

#include "Ascend/AI/AIEntityModule.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"


static FName NAME_DamageCollision(TEXT("Damage Collision"));

#pragma region Main
AMeleeWeapon::AMeleeWeapon()
{
	DamageCollision = CreateDefaultSubobject<UBoxComponent>(NAME_DamageCollision);
	DamageCollision->SetupAttachment(WeaponMesh);

	DamageCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	DamageCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	SetWeaponType(EWeaponType::EWT_Melee);
	FVector BoxExtent(2.0f, 2.0f, 40.0f);
	DamageCollision->SetBoxExtent(BoxExtent);

	if (DamageCollision)
	{
		UE_LOG(LogTemp, Warning, TEXT("DamageCollision is valid."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DamageCollision is NOT valid."));
	}
}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("MeleeWeapon");


	EditMeleeWeaponsByType();
}

void AMeleeWeapon::EditMeleeWeaponsByType()
{

	if (MeleeWeaponProperties.GetMeleeWeaponType() == EMeleeWeaponType::EMT_Sword)
	{

	}
	else if (MeleeWeaponProperties.GetMeleeWeaponType() == EMeleeWeaponType::EMT_Katana)
	{
		FVector BoxExtent(2.0f, 2.0f, 40.0f);
		DamageCollision->SetBoxExtent(BoxExtent);
	}
	else if (MeleeWeaponProperties.GetMeleeWeaponType() == EMeleeWeaponType::EMT_Axe)
	{

	}
	else if (MeleeWeaponProperties.GetMeleeWeaponType() == EMeleeWeaponType::EMT_Mace)
	{

	}
	else if (MeleeWeaponProperties.GetMeleeWeaponType() == EMeleeWeaponType::EMT_Dagger)
	{

	}
	else if (MeleeWeaponProperties.GetMeleeWeaponType() == EMeleeWeaponType::EMT_Club)
	{

	}
	else if (MeleeWeaponProperties.GetMeleeWeaponType() == EMeleeWeaponType::EMT_Spear)
	{

	}
	else if (MeleeWeaponProperties.GetMeleeWeaponType() == EMeleeWeaponType::EMT_Shield)
	{

	}
	else if (MeleeWeaponProperties.GetMeleeWeaponType() == EMeleeWeaponType::EMT_HiddenBlade)
	{

	}
}

#pragma endregion

#pragma region Weapon-Overlaps

void AMeleeWeapon::OnDamageCollisionBeginOverlap
(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	// Check if the overlapping actor is the owner of this weapon
	if (OtherActor == GetOwner())
	{
		// Do not proceed  if the overlapping actor is the owner
		return;
	}

	// Check if the overlapping component is valid and not simulating physics
	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		// Do no proceed if the overlapping component is simulating physics
		return;
	}




	// Check if the overlapping actor is an AI entity
	AAIEntityModule* AIEntity = Cast<AAIEntityModule>(OtherActor);
	if (AIEntity)
	{
		// if the overlapping actor belongs to the same owner as the ai entity
		if (OtherActor->GetOwner() == AIEntity->GetOwner())
		{
			// Handle interaction between this actor and AI entity of the same owner

		}
		else
		{
			// Handle interaction between this actor and AI entity of different owners
		}
	}

	// Check if the overlapping actor is a player character
	ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// if the overlapping actor belongs to the same owner as the player character
		if (OtherActor->GetOwner() == PlayerCharacter->GetOwner())
		{
			// Handle interaction between this actor and player character of the same owner 
		}
		else
		{
			// Handle interaction between this actor and player character of different owners
		}
	}
}





void AMeleeWeapon::ActivateWeaponOverlapDynamics(bool bActivate)
{
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnDamageCollisionBeginOverlap);

	if (DamageCollision->OnComponentBeginOverlap.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap event handler is bound."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap event handler is not bound."));

	}
}

bool AMeleeWeapon::IsActorSameType(AActor* OtherActor)
{
	return GetOwner()->ActorHasTag(TEXT("AI")) && OtherActor->ActorHasTag(TEXT("AI"));
}

#pragma endregion
