// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingInteraction.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

AMovingInteraction::AMovingInteraction()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);

	EndLocation = CreateDefaultSubobject<USceneComponent>(TEXT("End"));
	EndLocation->SetupAttachment(RootComponent);
}

void AMovingInteraction::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = PaperSprite->GetRelativeLocation();
	TargetLocation = EndLocation->GetRelativeLocation();
}

void AMovingInteraction::Move(const float& DurationTimeLine)
{
	const float ClampedTimeline = FMath::Clamp(DurationTimeLine, 0.0f, 1.0f);

	const FVector ActualTargetLocation = StartLocation + TargetLocation;

	const FVector NewLocation = FMath::Lerp(StartLocation, ActualTargetLocation, ClampedTimeline);

	if (PaperSprite)
	{
		PaperSprite->SetRelativeLocation(NewLocation);
	}
}
