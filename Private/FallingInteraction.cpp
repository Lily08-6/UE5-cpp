// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingInteraction.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFallingInteraction::AFallingInteraction()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(PaperSprite);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->SetActive(false);
}
void AFallingInteraction::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFallingInteraction::BoxBeginOverlaped);
}

void AFallingInteraction::BoxBeginOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerCharacter == nullptr)
	{
		return;
	}

	if (OtherActor == PlayerCharacter && !bAlreadyOnFall)
	{
		bAlreadyOnFall = true;
		UE_LOG(LogTemp, Warning, TEXT("Plateformer2D: begin overlapped"))
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFallingInteraction::OnFall, DropDelay, false);
	}
}

void AFallingInteraction::OnFall()
{
	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
		ProjectileMovementComponent->SetActive(true);

		if(PaperSprite)
		{
			PaperSprite->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFallingInteraction::OnReset, RespawnDelay, false);
	}
}

void AFallingInteraction::OnReset()
{
	if (FallingInteractionClass == nullptr)
	{
		return;
	}
	if (bDestroy)
	{
		Destroy();
	}
	if (bRespawn)
	{
		GetWorld()->SpawnActor<AFallingInteraction>(
		FallingInteractionClass,
		StartLocation,
		GetActorRotation()
		);
	}

	bAlreadyOnFall = false;
}
