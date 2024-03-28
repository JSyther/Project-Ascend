// @2023 All rights reversed by Reverse-Alpha Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ascend/Interface/CombatInterface.h"
#include "AIEntityModule.generated.h"

class AAIPatrolPath;

class UAnimMontage;
class UAttributeComponent;
class UAIDefaultAnimInstance;
class UBehaviorTree;
class UHealthBar;
class UWidgetComponent;

UCLASS()
class ASCEND_API AAIEntityModule : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAIEntityModule();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

#pragma region MainComps
protected:
	USkeletalMeshComponent* AIMesh;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* AICapsuleComponent;


	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* AttributeComponent;
#pragma endregion

#pragma region Combat
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeveloperProperties, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	int MeleeAttack_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeveloperProperties, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* DrawWeaponMontage;

public:
	UAnimMontage* GetAttackMontage() const { return AttackMontage; }

	UAnimMontage* GetDrawWeaponMontage() const { return DrawWeaponMontage; }

#pragma endregion
	
#pragma endregion
#pragma region AIProps
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeveloperProperties, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeveloperProperties, meta = (AllowPrivateAccess = "true"))
	AAIPatrolPath* AIPatrolPath;

public:
	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	AAIPatrolPath* GetAIPatrolPath() const { return AIPatrolPath; }
#pragma endregion
private:
	float DamageAmount;

public:
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void HandleDamage(float DamageValue);

#pragma region UI/Widgets
private:
	UPROPERTY(EditAnywhere, Category = DeveloperProperties)
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* HealthBarWidgetComponent;

	UPROPERTY()
	UHealthBar* HealthBarWidget;
#pragma endregion
};
