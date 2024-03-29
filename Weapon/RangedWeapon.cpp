// // @2023 All rights reversed by Reverse-Alpha Studios


#include "RangedWeapon.h"
#include "Ascend/Tools/LogMacros.h"

#include "Ascend/AI/AIEntityModule.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

#include "Projectile/ProjectileModule.h"

ARangedWeapon::ARangedWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	// Set WeaponType to represent a "Ranged" weapon
	SetWeaponType(EWeaponType::EWT_Ranged);
}

void ARangedWeapon::BeginPlay()
{
	Super::BeginPlay();

	SetRarityCategory(RangedWeaponProperties.GetRarityCategory());
	RangedWeaponProperties.UpdateWeaponPropertiesBasedOnRangedWeaponType(RangedWeaponProperties.GetRangedWeaponType());
}


void ARangedWeapon::Fire(const FVector& HitPoint, FHitResult& HitResult)
{
	const FName MuzzleFlashSocketName("MuzzleFlashSocket");
	FVector		MuzzleFlashSocketLocation	= WeaponMesh->GetSocketLocation(MuzzleFlashSocketName);
	FRotator	MuzzleFlashSocketRotation	= WeaponMesh->GetSocketRotation(MuzzleFlashSocketName);
	FVector		EndPoint = MuzzleFlashSocketLocation + (HitPoint - MuzzleFlashSocketLocation * 1.1f);

#pragma region Common Properties
	if (MuzzleFlash)
	{
		if (WeaponMesh->DoesSocketExist(MuzzleFlashSocketName))
		{
			UGameplayStatics::SpawnEmitterAttached
			(
				MuzzleFlash,
				WeaponMesh,
				MuzzleFlashSocketName,
				MuzzleFlashSocketLocation,
				MuzzleFlashSocketRotation,
				EAttachLocation::KeepWorldPosition
			);
		}
	}

	if (WeaponFireSound)
	{
		InsertAndPlaySound2D(WeaponFireSound);
	}

	if (ImpactPointParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation
		(
			GetWorld(),
			ImpactPointParticle,
			HitResult.ImpactPoint,
			HitResult.ImpactNormal.Rotation()
		);
	}

	if (ImpactPointSound)
	{
		InsertAndPlaySoundAtLocation(ImpactPointSound, HitPoint);
	}



#pragma region Damage
	// Retrieve the current equipped weapon's damage value.
	float WeaponDamage = RangedWeaponProperties.GetDamage();

	// Retrieve the current equipped weapon's penetration value.
	float WeaponPenetration = RangedWeaponProperties.GetPenetration();

	// Calculate the total damage by multiplying the weapon's damage by its penetration.
	float TotalDamage = WeaponDamage * WeaponPenetration;

	// Calculate the durability damage by dividing the total damage by a fixed divisor.

	// Default durability divisor
	float DurabilityDivisor;
	// Adjust divisor as needed for balancing
	if (RangedWeaponProperties.GetWeaponFireMode() == EWeaponFiringMode::SingleShot)
	{
		DurabilityDivisor = 2.0f;
	}
	else if (RangedWeaponProperties.GetWeaponFireMode() == EWeaponFiringMode::Automatic)
	{
		DurabilityDivisor = 5.50f;
	}
	else if (RangedWeaponProperties.GetWeaponFireMode() == EWeaponFiringMode::SemiAutomatic)
	{
		DurabilityDivisor = 5.50f;
	}

	float DurabilityDamage = TotalDamage / DurabilityDivisor;

	// Retrieve the current durability value of the ranged weapon.
	float CurrentWeaponDurability = RangedWeaponProperties.GetDurability();

	// Update the durability property by subtracting the calculated durability damage
	// This simulates wear and tear on the weapon due to its usage
	RangedWeaponProperties.SetDurability(CurrentWeaponDurability - DurabilityDamage);

#pragma region FireType
	if (RangedWeaponProperties.GetFireType() == EFireType::EFT_HitScan)
	{
		if (RangedWeaponProperties.GetWeaponFireMode() == EWeaponFiringMode::SingleShot)
		{
			if (bCanFire_HitScan)
			{

				bCanFire_HitScan = false;
			}
		}
		else if (RangedWeaponProperties.GetWeaponFireMode() == EWeaponFiringMode::SemiAutomatic)
		{
			if (bCanFire_HitScan)
			{

				bCanFire_HitScan = false;
			}
		}
		else if (RangedWeaponProperties.GetWeaponFireMode() == EWeaponFiringMode::Automatic)
		{
			if (bCanFire_HitScan)
			{

				bCanFire_HitScan = false;
			}
		}
		if (RangedWeaponOptions.bSpawnTrail == true)
		{
			if (BulletTrail)
			{
				UParticleSystemComponent* Tracer =
					UGameplayStatics::SpawnEmitterAtLocation
					(
						GetWorld(),
						BulletTrail,
						HitResult.TraceStart,
						FRotator::ZeroRotator,
						true
					);
			}
		}

		// Get the actor that was hit by a trace or collision
		AActor* FindActor = HitResult.GetActor();
		if (FindActor)
		{
			// If an actor is found, get its class.
			UClass* ActorClass = FindActor->GetClass();

			// Get the superclass of the actor's class.
			UClass* SuperClass = ActorClass->GetSuperClass();

			// Get the superclass of the superclass.
			UClass* UpperSuperClass = SuperClass->GetSuperClass();

			//Get the superclass of the upper superclass(which is class "AAIEntityModule").
			UClass* DesiredSuperClass = UpperSuperClass->GetSuperClass();

			// Check if the desired superclass matches a specific class (e.g., AIEntityModule).
			if (DesiredSuperClass == AAIEntityModule::StaticClass())
			{
				// If the desired superclass matches the specific class, attempt to cast it to AAIEntityModule.
				AAIEntityModule* AIEntity = Cast<AAIEntityModule>(HitResult.GetActor());
				if (AIEntity)
				{
					// If successful, apply damage to the AI entity using GameplayStatics.
					UGameplayStatics::ApplyDamage
					(
						AIEntity,
						TotalDamage,
						BaseCharacter->GetInstigatorController(),
						this,
						UDamageType::StaticClass()
					);
				}
			}
		}
	}
	else if (RangedWeaponProperties.GetFireType() == EFireType::EFT_Projectile)
	{
		APawn* InstigatorPawn						= Cast<APawn>(GetOwner());
		AProjectileModule* ProjectileModuleInstance = nullptr;

		FVector TargetLocation = HitPoint - MuzzleFlashSocketLocation;
		FRotator TargetRotation = TargetLocation.Rotation();

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner		= GetOwner();
		SpawnParameters.Instigator	= InstigatorPawn;
		
		AProjectileModule* ProjectileClass = GetWorld()->SpawnActor<AProjectileModule>
		(
			ProjectModule,
			MuzzleFlashSocketLocation,
			TargetRotation,
			SpawnParameters
		);

		// Get the actor that was hit by a trace or collision
		AActor* FindActor = HitResult.GetActor();
		if (FindActor)
		{
			// If an actor is found, get its class.
			UClass* ActorClass = FindActor->GetClass();

			// Get the superclass of the actor's class.
			UClass* SuperClass = ActorClass->GetSuperClass();

			// Get the superclass of the superclass.
			UClass* UpperSuperClass = SuperClass->GetSuperClass();

			//Get the superclass of the upper superclass(which is class "AAIEntityModule").
			UClass* DesiredSuperClass = UpperSuperClass->GetSuperClass();

			// Check if the desired superclass matches a specific class (e.g., AIEntityModule).
			if (DesiredSuperClass == AAIEntityModule::StaticClass())
			{
				// If the desired superclass matches the specific class, attempt to cast it to AAIEntityModule.
				AAIEntityModule* AIEntity = Cast<AAIEntityModule>(HitResult.GetActor());
				if (AIEntity)
				{
					if (ProjectileClass)
					{
						ProjectileClass->ReceiveAndApplyDamageAmount(AIEntity,TotalDamage, BaseCharacter->GetInstigatorController());
					}

					if (AIEntity->IsAIDead())
					{
						if (HitResult.IsValidBlockingHit())
						{
							UPrimitiveComponent* Target = HitResult.GetComponent();

							AActor* OwnerActor = Target->GetOwner();
							if (OwnerActor)
							{
								FVector NewVelocity = FVector(500.0f, 0.0f, 0.0f);

								Target->SetPhysicsLinearVelocity(NewVelocity);
								LW("DONETARGET");
							}
						}
					}
					LW("PROJECTILE TO ENTITY");
				}
			}
		}
	}


#define LOG_WEAPON_PROPERTIES 0
#if LOG_WEAPON_PROPERTIES == 0
	LW_TF("WeaponDamage: %f", WeaponDamage);
	LW_TF("CurrentDurability: %f", CurrentWeaponDurability);
	LW_TF("Durability Damage: %f", DurabilityDamage);
#endif

}
