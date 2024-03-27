// // @2023 All rights reversed by Reverse-Alpha Studios

#include "MeleeWeapon.h"

#include "Ascend/AI/AIEntityModule.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Actor.h"


static FName NAME_DamageCollision(TEXT("Damage Collision"));

AMeleeWeapon::AMeleeWeapon()
{
	DamageCollision = CreateDefaultSubobject<UBoxComponent>(NAME_DamageCollision);
	DamageCollision->SetupAttachment(WeaponMesh);

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnDamageCollisionBeginOverlap);
	SetWeaponType(EWeaponType::EWT_Melee);
}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
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



void AMeleeWeapon::OnDamageCollisionBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAIEntityModule* AIEntity = Cast<AAIEntityModule>(OtherActor);

	if (AIEntity)
	{
		const FMeleeWeaponProperties& WeaponProperties = GetMeleeWeaponProperties();
		const float DamageAmount = WeaponProperties.GetDamageValue();
		FDamageEvent DamageEvent;
		AController* EventInstigator = GetInstigatorController();
		AActor* DamageCauser = this;

		AIEntity->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);	
		UE_LOG(LogTemp, Warning, TEXT("DamageDone"));
	}
}