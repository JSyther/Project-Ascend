// @2023 All rights reversed by Reverse-Alpha Studios


#include "AIEntityModule.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

#include "Ascend/Component/AttributeComponent.h"
#include "Ascend/Widget/HealthBar.h"


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

	static FName NAME_Attribute(TEXT("Attribute Component"));

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(NAME_Attribute);	

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(GetMesh()); 
	HealthBarWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f)); 
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidgetClassFinder(TEXT("/Game/Blueprints/UI/WBP_HealthBar"));

	if (HealthBarWidgetClassFinder.Succeeded())
	{
		HealthBarWidgetClass = HealthBarWidgetClassFinder.Class;
	}
}

void AAIEntityModule::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (AttributeComponent)
	{
		AttributeComponent->SetAIEntityModule(this);
	}
}

void AAIEntityModule::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("AIEntity");

	if (HealthBarWidgetClass)
	{
		HealthBarWidget = CreateWidget<UHealthBar>(GetWorld(), HealthBarWidgetClass);
		if (HealthBarWidget)
		{
			HealthBarWidgetComponent->SetWidget(HealthBarWidget);
			HealthBarWidget->SetBarValuePercent(AttributeComponent->GetHealth() / AttributeComponent->GetMaxHealth());
		}
	}
}

void AAIEntityModule::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

int AAIEntityModule::MeleeAttack_Implementation()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}
	return 0;
}


float AAIEntityModule::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	HandleDamage(DamageAmount);
	HealthBarWidget->SetBarValuePercent(AttributeComponent->GetHealth() / AttributeComponent->GetMaxHealth());
	return DamageAmount;
}

void AAIEntityModule::HandleDamage(float DamageValue)
{
	if (AttributeComponent != nullptr)
	{
		if (AttributeComponent->GetHealth() <= 0) return;
		float CurrentHealth = AttributeComponent->GetHealth();
		float GetMaxHealth	= AttributeComponent->GetMaxHealth();
		float NewHealth		= CurrentHealth - DamageValue;
		NewHealth			= FMath::Clamp(NewHealth, 0.0f, GetMaxHealth);
		AttributeComponent->SetHealth(NewHealth);
	}
}
