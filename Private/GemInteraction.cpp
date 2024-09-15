// Fill out your copyright notice in the Description page of Project Settings.


#include "GemInteraction.h"

#include "CharacterGameComponent.h"
#include "FxTrack.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Plateformer2DCharacter.h"
#include "PlayerStatWidget.h"


AGemInteraction::AGemInteraction()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collision"));
	BoxComponent->SetupAttachment(PaperSprite);
}

void AGemInteraction::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGemInteraction::BoxBeginOverlaped);
}

void AGemInteraction::BoxBeginOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerCharacter == nullptr)
	{
		return;
	}

	if (OtherActor == PlayerCharacter && (OtherActor != this))
	{
		if (UCharacterGameComponent* CharacterGameComponent = PlayerCharacter->FindComponentByClass<UCharacterGameComponent>())
		{
			const float CurrentGem = CharacterGameComponent->IncrementGem();

			CharacterGameComponent->GetPlayerStatWidget()->UpdateNbGem(CurrentGem);

			UFxTrack::Play2DSoundFX(this, ETrackSound::NotificationSound);

			Destroy();
		}
	}
}

void AGemInteraction::BoxEndOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
