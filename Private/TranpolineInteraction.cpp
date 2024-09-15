// Fill out your copyright notice in the Description page of Project Settings.


#include "TranpolineInteraction.h"

#include "FxTrack.h"
#include "Plateformer2DCharacter.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

ATranpolineInteraction::ATranpolineInteraction()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collision"));
	BoxComponent->SetupAttachment(PaperSprite);
}

void ATranpolineInteraction::BeginPlay()
{
	Super::BeginPlay();

	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATranpolineInteraction::BoxBeginOverlaped);
	}
	
}

void ATranpolineInteraction::BoxBeginOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerCharacter == nullptr)
	{
		return;
	}
	if (OtherActor == PlayerCharacter && (OtherActor != this))
	{
		PlayerCharacter->LaunchCharacter(LaunchVelocity, false, true);
		if (SpriteTrampolineUp)
		{
			PaperSprite->SetSprite(SpriteTrampolineUp);

			UFxTrack::Play2DSoundFX(this, ETrackSound::TrampolineSound);
			
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATranpolineInteraction::ResetTrampoline, Duration, false);
		}
	}
}

void ATranpolineInteraction::ResetTrampoline()
{
	PaperSprite->SetSprite(SpriteTrampolineDown);
}
