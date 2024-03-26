// // @2023 All rights reversed by Reverse-Alpha Studios


#include "RangedWeapon.h"
#include "Ascend/Character/ShortDebugMacros.h"

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


	if (RangedWeaponProperties.GetFireType() == EFireType::EFT_HitScan)
	{
		FVector EndPoint = MuzzleFlashSocketLocation + (HitPoint - MuzzleFlashSocketLocation * 1.1f);

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
				LW("SPAWNED EMITTER BULLET TRAIL");
			}
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
	}
	else if (RangedWeaponProperties.GetFireType() == EFireType::EFT_Projectile)
	{
		APawn* InstigatorPawn						= Cast<APawn>(GetOwner());
		AProjectileModule* ProjectileModuleInstance = nullptr;


		FVector TargetLocation = HitPoint - MuzzleFlashSocketLocation;
		FRotator TargetRotation = TargetLocation.Rotation();


		FActorSpawnParameters SpawmParameters;
		SpawmParameters.Owner = GetOwner();
		SpawmParameters.Instigator = InstigatorPawn;
		
		GetWorld()->SpawnActor<AProjectileModule>
		(
			ProjectModule,
			MuzzleFlashSocketLocation,
			TargetRotation,
			SpawmParameters
		);
	}




/*Applying Damage*/

	//AController* InstigatorController = OwnerPawn->GetController();
	//if (InstigatorController != nullptr)
	//{
	//	UGameplayStatics::ApplyDamage
	//	(
	//		DamagedActor,
	//		WeaponDamage,
	//		InstigatorController,
	//		this,
	//		UDamageType::StaticClass()
	//	);
	//}
	//else
	//{
	//	LW("INTIGATOR CONTROLLER IS NULLPTR")
	//}
}