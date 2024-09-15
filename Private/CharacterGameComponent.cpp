// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterGameComponent.h"

#include "DeathComponent.h"
#include "EnemyBase.h"
#include "HealthComponent.h"
#include "Plateformer2DCharacter.h"
#include "PlayerStatWidget.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCharacterGameComponent::UCharacterGameComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterGameComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	CurrentCharacter = Cast<APlateformer2DCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Owner && CurrentCharacter)
	{
		RespawnLocation = Owner->GetActorLocation();
	}

	if (PlayerStatWidgetClass)
	{
		PlayerStatWidget = NewObject<UPlayerStatWidget>(this, PlayerStatWidgetClass);
		PlayerStatWidget->AddToViewport();
	}
	
}


// Called every frame
void UCharacterGameComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterGameComponent::MoveLeftRight(const FInputActionValue& Value)
{
	if (CurrentCharacter && Value.GetMagnitude() != 0.f)
	{
		FVector WorldDirection = FVector(1.f, 0.f, 0.f);
		CurrentCharacter->AddMovementInput(WorldDirection, Value.GetMagnitude(), false);
	}
}

void UCharacterGameComponent::MoveUpAndDown(const FInputActionValue& Value)
{
	if (CurrentCharacter && Value.GetMagnitude() != 0.f)
	{
		FVector WorldDirection = FVector(0.f, 0.f, 1.f);
		CurrentCharacter->AddMovementInput(WorldDirection, Value.GetMagnitude(), false);
	}
}

void UCharacterGameComponent::Jump()
{
	bJumping = true;
}

void UCharacterGameComponent::RespawnCharacter(FVector Location, bool bRelife)
{
	if (Owner)
	{
		Owner->SetActorLocation(Location);

		UDeathComponent* DeathComponent = Owner->FindComponentByClass<UDeathComponent>();
		if (DeathComponent)
		{
			DeathComponent->SetIsDead(false);
		}

		if (bRelife)
		{
			UHealthComponent* HealthComponent = Owner->FindComponentByClass<UHealthComponent>();
			HealthComponent->Relife();
		}
	}
}

float UCharacterGameComponent::IncrementGem()
{
	Gem += 1;
	return Gem;
}

void UCharacterGameComponent::CapsuleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	
	EnemyBase = Cast<AEnemyBase>(OtherActor);
	
	if (EnemyBase)
	{
		if (EnemyBase == OtherActor && EnemyBase->IsCanTakeDamage())
		{
			const FVector CurrentActorLocation = CurrentCharacter->GetActorLocation();
			const FVector CapsuleHitLocation = Hit.Location;

			FVector HitDirection = CapsuleHitLocation - CurrentActorLocation;
			HitDirection = HitDirection.GetSafeNormal(0.0f);

			if (HitDirection.Z <= -0.3f)
			{
				EnemyBase->TakeDamage(DefaultDamageAmount, FDamageEvent(), nullptr, nullptr);
			}
			else
			{
				CurrentCharacter->TakeDamage(EnemyBase->GetDefaultDamageAmount(),FDamageEvent(), nullptr, nullptr);
			}
		}
	}
}


