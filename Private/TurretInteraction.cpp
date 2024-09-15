// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretInteraction.h"
#include "PaperSpriteComponent.h"
#include "ProjectileParent.h"

// Sets default values
ATurretInteraction::ATurretInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	RootComponent = PaperSprite;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SceneComponent->SetupAttachment(PaperSprite);	

}

// Called when the game starts or when spawned
void ATurretInteraction::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TurretTimerHandle, this, &ATurretInteraction::Fire, DurationSpawn, bLooping);
	
}

// Called every frame
void ATurretInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurretInteraction::Fire()
{
	if (ProjectileClass)
	{
		AProjectileParent* ProjectileParent = GetWorld()->SpawnActor<AProjectileParent>(
			ProjectileClass,
			SceneComponent->GetComponentLocation(),
			SceneComponent->GetComponentRotation()
		);

		if (ProjectileParent)
		{
			ProjectileParent->SetOwner(this);
		}
	}
}

