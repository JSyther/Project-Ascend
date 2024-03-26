// // @2023 All rights reversed by Reverse-Alpha Studios

#pragma once
#include "BaseWeapon.h"
#include "RangedWeapon.generated.h"

class AProjectileModule;

USTRUCT(BlueprintType)
struct FRangedWeaponProperties
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFireType FireType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERangedWeaponType RangedWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EWeaponFiringMode WeaponFireMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAmmunitionType AmmunitionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERarityCategory RarityCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Penetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Accuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MagazineCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Price;

	UPROPERTY()
	TArray<AActor*> SpecialEffects;

public:
	FRangedWeaponProperties()
		: FireType(EFireType::EFT_Default),
		RangedWeaponType(ERangedWeaponType::Default),
		WeaponFireMode(EWeaponFiringMode::Default),
		AmmunitionType(EAmmunitionType::Default),
		RarityCategory(ERarityCategory::Common),
		Damage(0.0f),
		Penetration(0.0f),
		Range(0.0f),
		Accuracy(0.0f),
		MagazineCapacity(0),
		FireRate(0.0f),
		ReloadTime(0.0f),
		Weight(0.0f),
		Price(0.0f)
	{

	}

public:
	void UpdateWeaponPropertiesBasedOnRangedWeaponType(ERangedWeaponType InsertRangedWeaponType)
	{
		switch (InsertRangedWeaponType)
		{
		case ERangedWeaponType::ERT_Pistol:
			WeaponFireMode = EWeaponFiringMode::SingleShot;
			AmmunitionType = EAmmunitionType::EAT_45ACP;
			break;
		case ERangedWeaponType::ERT_Shotgun:
		case ERangedWeaponType::ERT_Sniper:
		case ERangedWeaponType::ERT_Bow:
		case ERangedWeaponType::ERT_Crossbow:
		case ERangedWeaponType::ERT_Throwing:
		case ERangedWeaponType::ERT_Launcher:
		case ERangedWeaponType::ERT_Cannon:
			WeaponFireMode = EWeaponFiringMode::SingleShot;
			break;
		case ERangedWeaponType::ERT_Rifle:
			WeaponFireMode = EWeaponFiringMode::Automatic;
			AmmunitionType = EAmmunitionType::EAT_556mm;
			switch (RarityCategory)
			{
			case ERarityCategory::Common:
				Damage				= FMath::RandRange(21.0f, 23.0f);
				Penetration			= FMath::RandRange(1.0f, 1.1f);
				Range				= FMath::RandRange(250.0f, 300.0f);
				Accuracy			= 70.0f;
				MagazineCapacity	= 30;
				FireRate			= 0.15f;
				ReloadTime			= 2.5f;
				Weight				= 1450.0f;
				Price				= 80.0f;
				break;
			case ERarityCategory::Rare:
				Damage				= FMath::RandRange(23.0f, 25.0f);
				Penetration			= FMath::RandRange(1.1f, 1.2f);
				Range				= FMath::RandRange(300.0f, 350.0f);
				Accuracy			= 75.0f;
				MagazineCapacity	= 32;
				FireRate			= 0.14f;
				ReloadTime			= 2.3f;
				Weight				= 1350.0f;
				Price				= 90.0f;
				break;
			case ERarityCategory::Epic:
				Damage				= FMath::RandRange(25.0f, 27.0f);
				Penetration			= FMath::RandRange(1.2f, 1.3f);
				Range				= FMath::RandRange(350.0f, 400.0f);
				Accuracy			= 80.0f;
				MagazineCapacity	= 34;
				FireRate			= 0.13f;
				ReloadTime			= 2.1f;
				Weight				= 1250.0f;
				Price				= 100.0f;
				break;
			case ERarityCategory::Unique:
				Damage				= FMath::RandRange(28.0f, 31.0f);
				Penetration			= FMath::RandRange(1.3f, 1.5f);
				Range				= FMath::RandRange(400.0f, 450.0f);
				Accuracy			= 85.0f;
				MagazineCapacity	= 40;
				FireRate			= 0.10f;
				ReloadTime			= 1.8f;
				Weight				= 1.000f;
				Price				= 120.0f;
				break;
			default:
				UE_LOG(LogTemp, Fatal, TEXT("Check"));
				break;
			}
			break;
		case ERangedWeaponType::ERT_Submachine:
		case ERangedWeaponType::ERT_Heavymachine:
			WeaponFireMode = EWeaponFiringMode::Automatic;
			AmmunitionType = EAmmunitionType::EAT_556mm;
			break;
		default:
			WeaponFireMode = EWeaponFiringMode::Default;
			break;
		}
	}

public:
	EFireType GetFireType() const
	{ 
		return FireType; 
	}
	ERangedWeaponType GetRangedWeaponType() const 
	{
		return RangedWeaponType;
	}

	EWeaponFiringMode GetWeaponFireMode() const
	{ 
		return WeaponFireMode;
	}

	EAmmunitionType GetAmmunitionType() const 
	{
		return AmmunitionType;
	}

	ERarityCategory GetRarityCategory() const
	{
		return RarityCategory;
	}
	float GetDamage() const
	{
		return Damage;
	}
	float GetPenetration()
	{
		return Penetration;
	}
	float GetRange()
	{
		return Range;
	}
	float GetAccuracy()
	{
		return Accuracy;
	}
	int32 GetMagazineCapacity()
	{
		return MagazineCapacity;
	}
	float GetFireRate()
	{
		return FireRate;
	}
	float GetReloadTime()
	{
		return ReloadTime;
	}
	float GetWeight()
	{
		return Weight;
	}
	float GetPrice()
	{
		return Price;
	}
	
	void SetRangedWeaponType(ERangedWeaponType newWeaponType) { RangedWeaponType = newWeaponType; }
	void SetWeaponFireMode(EWeaponFiringMode newFireMode) { WeaponFireMode = newFireMode; }

};


USTRUCT(BlueprintType)
struct FRangedWeaponOptions
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool bSpawnTrail = false;

	UPROPERTY(EditAnywhere)
	bool bFlashLight = false;

	UPROPERTY(EditAnywhere)
	bool bLaserSight = false;
};

UCLASS()
class ASCEND_API ARangedWeapon : public ABaseWeapon
{
	GENERATED_BODY()

#pragma region Fundementals
protected:
	ARangedWeapon();
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DeveloperProperties)
	FRangedWeaponProperties RangedWeaponProperties;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DeveloperProperties)
	FRangedWeaponOptions RangedWeaponOptions;

public:
	FRangedWeaponProperties GetRangedWeaponProperties() const { return RangedWeaponProperties; }
#pragma endregion

#pragma region FireSystem
public:
	virtual void Fire(const FVector& HitPoint, FHitResult& HitResult);


/*Fire Types*/
private:
	UPROPERTY(EditAnywhere, Category = "DeveloperProperties")
	TSubclassOf<AProjectileModule> ProjectModule;

#pragma endregion
#pragma region Camera Properties
private:
	UPROPERTY(EditAnywhere, Category = DeveloperProperties)
	float ZoomedFOV			= 30.0f;

	UPROPERTY(EditAnywhere, Category = DeveloperProperties)
	float ZoomInterpSpeed	= 20.0f;

#pragma endregion 
#pragma region VisiualFXs & Sounds
private:
/*Visual*/
	UPROPERTY(EditAnywhere, Category = "DeveloperProperties|WeaponEffects")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "DeveloperProperties|WeaponEffects")
	UParticleSystem* BulletTrail;

	UPROPERTY(EditAnywhere, Category = "DeveloperProperties|WeaponEffects")
	UParticleSystem* ImpactPointParticle;

/*Sounds*/
	UPROPERTY(EditAnywhere, Category = "DeveloperProperties|WeaponSounds")
	USoundCue* WeaponFireSound;

	UPROPERTY(EditAnywhere, Category = "DeveloperProperties|WeaponSounds")
	USoundCue* ImpactPointSound;

#pragma endregion
};
