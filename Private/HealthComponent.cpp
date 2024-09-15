// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "DeathComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}



void UHealthComponent::Relife()
{
	if (Owner == nullptr)
	{
		return;
	}
	
	Health = DefaultHealth;
	if (UDeathComponent* DeathComponent = Owner->FindComponentByClass<UDeathComponent>())
	{
		DeathComponent->SetIsDead(false);
	}
}

void UHealthComponent::InitHealth()
{
	if (Owner == nullptr)
	{
		return;
	}
	
	// Todo: On implementing save game
}

float UHealthComponent::TakeDamage(const float& Damage)
{
	UDeathComponent* DeathComponent = Owner->FindComponentByClass<UDeathComponent>();

	if (DeathComponent && Health >= 0.f)
	{
		Health -= Damage;
		Health = FMath::Clamp(Health, 0.f, DefaultHealth);
		if (Health == 0.f && !DeathComponent->IsDead())
		{
			DeathComponent->OnDeath();
		}
	}

	return Health;
}

