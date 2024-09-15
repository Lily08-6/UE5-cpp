// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeInteraction.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Plateformer2DCharacter.h"
#include "Engine/DamageEvents.h"


ASpikeInteraction::ASpikeInteraction()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxComponent->SetupAttachment(PaperSprite);
}

void ASpikeInteraction::ChangeSpikeStat()
{
	bSpikeUp = !bSpikeUp;
	UE_LOG(LogTemp, Warning, TEXT("Spikes status: %s"), bSpikeUp ? TEXT("UP") : TEXT("DOWN"));
	
	if (bSpikeUp)
	{
		BringSpikeDown();
	}
	else
	{
		BringSpikeUp();
	}
}

void ASpikeInteraction::BringSpikeUp()
{
	if (SpriteSpikeUp)
	{
		PaperSprite->SetSprite(SpriteSpikeUp);
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ASpikeInteraction::BringSpikeDown()
{
	if (SpriteSpikeDown)
	{
		PaperSprite->SetSprite(SpriteSpikeDown);
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ASpikeInteraction::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpikeInteraction::BoxBeginOverlaped);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpikeInteraction::ChangeSpikeStat, Duration, bLooping);
}

void ASpikeInteraction::BoxBeginOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerCharacter == OtherActor)
	{
		PlayerCharacter->TakeDamage(DamageAmount, FDamageEvent(), nullptr, nullptr);
	}
}