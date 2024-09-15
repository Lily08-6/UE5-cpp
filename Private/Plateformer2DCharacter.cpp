// Fill out your copyright notice in the Description page of Project Settings.


#include "Plateformer2DCharacter.h"
#include "CharacterGameComponent.h"
#include "AnimationComponent.h"
//#include "DeathComponent.h"
#include "DeathComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FxTrack.h"
#include "HealthComponent.h"
#include "PlayerStatWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlateformer2DCharacter::APlateformer2DCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SceneComponent->SetupAttachment(RootComponent);

	CharacterGameComponent = CreateDefaultSubobject<UCharacterGameComponent>(TEXT("Character"));
	AnimationComponent = CreateDefaultSubobject<UAnimationComponent>(TEXT("Animation"));
	
	DeathComponent = CreateDefaultSubobject<UDeathComponent>(TEXT("Death"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));


}
void APlateformer2DCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APlateformer2DCharacter::OnComponentHit);
}


void APlateformer2DCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (CharacterGameComponent)
	{
		CharacterGameComponent->SetJumping(false);
	}
}

void APlateformer2DCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MovementAction)
		{
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlateformer2DCharacter::EnhancedMove);
		}

		if (ClimbAction)
		{
			PlayerEnhancedInputComponent->BindAction(ClimbAction, ETriggerEvent::Triggered, this, &APlateformer2DCharacter::EnhancedClimb);
		}

		if (JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlateformer2DCharacter::EnhancedJump);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlateformer2DCharacter::StopJumping);
		}
	}
}

float APlateformer2DCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (HealthComponent)
	{
		float UpdatedHealth = HealthComponent->TakeDamage(ActualDamage);

		if (UpdatedHealth == 0.f)
		{
			CharacterGameComponent->RespawnCharacter(CharacterGameComponent->GetRespawnLocation(), true);
			UpdatedHealth = HealthComponent->GetHealth();
		}

		float MaxHealth = HealthComponent->GetDefaultHealth();
		
		if (CharacterGameComponent)
		{
			CharacterGameComponent->GetPlayerStatWidget()->UpdateHealthBar(UpdatedHealth, MaxHealth);
		}
	}
	
	return ActualDamage;
}

void APlateformer2DCharacter::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (CharacterGameComponent)
	{
		CharacterGameComponent->CapsuleComponentHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
	}
}

void APlateformer2DCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	Super::PawnClientRestart();

	if (APlayerController* LocalPlayer = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMappingContext, InputMappingPriority);
		}
	}
}

void APlateformer2DCharacter::EnhancedMove(const FInputActionValue& Value)
{
	if (CharacterGameComponent)
	{
		CharacterGameComponent->MoveLeftRight(Value);
	}
}

void APlateformer2DCharacter::EnhancedJump(const FInputActionValue& Value)
{
	if (CharacterGameComponent)
	{
		Super::Jump();
		UFxTrack::Play2DSoundFX(this, ETrackSound::JumpSound);
		CharacterGameComponent->Jump();
	}
}

void APlateformer2DCharacter::EnhancedClimb(const FInputActionValue& Value)
{
	if (CharacterGameComponent)
	{
		CharacterGameComponent->MoveUpAndDown(Value);
	}
}

