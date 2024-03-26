// // @2023 All rights reversed by Reverse-Alpha Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileModule.generated.h"

class UBoxComponent;
class UParticleSystem;
class UParticleSystemComponent;
class UProjectileMovementComponent;
class USoundCue;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class ASCEND_API AProjectileModule : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileModule();

protected:
	virtual void BeginPlay() override;

protected:
	/*ProjectileMovement*/
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	float ProjectileInitialSpeed;

	UPROPERTY(EditAnywhere)
	float ProjectileMaxSpeed;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;

	UPROPERTY()
	UParticleSystemComponent* TracerComponent;

	UPROPERTY(EditAnywhere, Category = "WeaponSettings")
	UParticleSystem* ProjectileTracer;

	UPROPERTY(EditAnywhere, Category = "WeaponSettings")
	UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, Category = "WeaponSettings")
	USoundCue* ImpactSound;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* TrailSystem;

	UPROPERTY()
	UNiagaraComponent* TrailSystemComponent;

	UPROPERTY(EditAnywhere)
	float ExplosiveDamage   = FMath::FRandRange(50.0f, 100.0f);

	UPROPERTY(EditAnywhere)
	float InnerRadiusDamage = FMath::FRandRange(50.0f, 100.0f);

	UPROPERTY(EditAnywhere)
	float OuterRadiusDamage = FMath::FRandRange(50.0f, 100.0f);

protected:
	UPROPERTY(EditAnywhere)
	float DestroyTime = 3.0f;

	FTimerHandle DestroyTimer;

	void SpawnTrailSystem();

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	virtual void OnExplodeDamage();

	virtual void Destroyed() override;
	void StartDestroyTimer();
	void DestroyTimerFinished();



};
