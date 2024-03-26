// // @2023 All rights reversed by Reverse-Alpha Studios

#pragma once

#include "BaseWeapon.h"
#include "MeleeWeapon.generated.h"

USTRUCT(BlueprintType)
struct FMeleeWeaponProperties
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERarityCategory RarityCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMeleeWeaponType MeleeWeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PenetrationValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Durability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Price;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AActor*> SpecialEffects;
};

UCLASS()
class ASCEND_API AMeleeWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	AMeleeWeapon();
	virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DeveloperProperties)
    FMeleeWeaponProperties MeleeWeaponProperties;

public:
    FMeleeWeaponProperties GetMeleeWeaponProperties() const { return MeleeWeaponProperties; }
};
