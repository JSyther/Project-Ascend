// @2023 All rights reversed by Reverse-Alpha Studios


#include "AIEntityModule.h"

#include "Components/CapsuleComponent.h"

#include "GameFramework/CharacterMovementComponent.h"


AAIEntityModule::AAIEntityModule()
{
	PrimaryActorTick.bCanEverTick = true;

	AICapsuleComponent = GetCapsuleComponent();
	check(AICapsuleComponent);
	SetRootComponent(AICapsuleComponent);

	AICapsuleComponent->InitCapsuleSize(35.0f, 89.95);
	AICapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	AICapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	AIMesh = GetMesh();
	check(AIMesh);
	
	FVector  MeshRelativeLocation = FVector(0.0f, 0.0f, -93.0f);
	FRotator MeshRelativeRotation = FRotator(0.0f, -90.0f, 0.0f);

	AIMesh->SetupAttachment(AICapsuleComponent);
	AIMesh->SetRelativeLocation(MeshRelativeLocation);
	AIMesh->SetRelativeRotation(MeshRelativeRotation);
	AIMesh->SetCastHiddenShadow(false);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AAIEntityModule::BeginPlay()
{
	Super::BeginPlay();
	
}

int AAIEntityModule::MeleeAttack_Implementation()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}
	return 0;
}
