// @2023 All rights reversed by Reverse-Alpha Studios


#include "AIMeleeHumanoidModule.h"
#include "Components/SphereComponent.h"
AAIMeleeHumanoidModule::AAIMeleeHumanoidModule()
{

}

void AAIMeleeHumanoidModule::BeginPlay()
{
	Super::BeginPlay();
	SpawnAndAttachMeleeWeapon();
}

void AAIMeleeHumanoidModule::SpawnAndAttachMeleeWeapon()
{
	if (bSpawnWithWeapon)
	{
		if (MeleeWeapons.Num() == 0) return;

		USkeletalMeshComponent* CharacterMesh = GetMesh();
		if (CharacterMesh == nullptr) return;

		int32 RandomIndex = FMath::RandRange(0, MeleeWeapons.Num() - 1);

		TSubclassOf<AMeleeWeapon> SelectedMeleeWeaponClass = MeleeWeapons[RandomIndex];


		FName SocketName = "RH_KatanaSocket";

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = GetInstigator();

		AMeleeWeapon* SpawnedMeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>
			(
				SelectedMeleeWeaponClass,
				GetActorLocation(),
				GetActorRotation(),
				SpawnParameters
			);

		if (SpawnedMeleeWeapon)
		{
			//SpawnedMeleeWeapon->GetAreaCollision()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//SpawnedMeleeWeapon->GetWeaponMesh()->SetSimulatePhysics(false);
			//SpawnedMeleeWeapon->GetWeaponMesh()->SetEnableGravity(false);
			//SpawnedMeleeWeapon->GetWeaponMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			SpawnedMeleeWeapon->SetWeaponState(EWeaponState::EWS_Equipped);
			SpawnedMeleeWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
			SpawnedMeleeWeapon->SetInstigator(GetInstigator());
			SpawnedMeleeWeapon->SetOwner(GetOwner());
			SpawnedMeleeWeapon->ActivateWeaponOverlapDynamics(true);
			SetMeleeWeaponClass(SpawnedMeleeWeapon);
		}
	}
}
