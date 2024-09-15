// Fill out your copyright notice in the Description page of Project Settings.


#include "LadderInteraction.h"
#include "CharacterGameComponent.h"
#include "Plateformer2DCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALadderInteraction::ALadderInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ALadderInteraction::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALadderInteraction::BoxBeginOverlaped);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ALadderInteraction::BoxEndOverlaped);

	AController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		APawn* CurrentCharacter = PlayerController->GetPawn();
		PlayerCharacter = Cast<APlateformer2DCharacter>(CurrentCharacter);
	}
	
}

// Called every frame
void ALadderInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALadderInteraction::BoxBeginOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == PlayerCharacter)
	{
		PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

		if (UCharacterGameComponent* CharacterGameComponent = PlayerCharacter->FindComponentByClass<UCharacterGameComponent>())
		{
			CharacterGameComponent->SetOnLadder(true);
		}
	}
}

void ALadderInteraction::BoxEndOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == PlayerCharacter)
	{
		PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

		if (UCharacterGameComponent* CharacterGameComponent = PlayerCharacter->FindComponentByClass<UCharacterGameComponent>())
		{
			CharacterGameComponent->SetOnLadder(false);
		}
	}
}

