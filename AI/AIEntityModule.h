// @2023 All rights reversed by Reverse-Alpha Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ascend/Interface/CombatInterface.h"
#include "AIEntityModule.generated.h"

class AAIPatrolPath;

class UAnimMontage;
class UAIDefaultAnimInstance;
class UBehaviorTree;

UCLASS()
class ASCEND_API AAIEntityModule : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAIEntityModule();

protected:
	virtual void BeginPlay() override;

#pragma region MainComps
protected:
	USkeletalMeshComponent* AIMesh;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* AICapsuleComponent;

	UPROPERTY()
	UAIDefaultAnimInstance* AIAnimInstance;



#pragma endregion

#pragma region Combat
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DeveloperProperties, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	int MeleeAttack_Implementation() override;

public:
	UAnimMontage* GetAttackMontage() const { return AttackMontage; }
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
};
