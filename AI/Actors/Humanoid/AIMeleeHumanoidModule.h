// @2023 All rights reversed by Reverse-Alpha Studios

#pragma once

#include "CoreMinimal.h"
#include "Ascend/AI/Actors/Humanoid/AIHumanoidModule.h"
#include "AIMeleeHumanoidModule.generated.h"

class AMeleeWeapon;

UCLASS()
class ASCEND_API AAIMeleeHumanoidModule : public AAIHumanoidModule
{
	GENERATED_BODY()
	
public:
	AAIMeleeHumanoidModule();

	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere)
	bool bSpawnWithWeapon = false;

	UPROPERTY(EditAnywhere, Category = DeveloperProperties)
	TArray<TSubclassOf<AMeleeWeapon>> MeleeWeapons;

	void SpawnAndAttachMeleeWeapon();
};
