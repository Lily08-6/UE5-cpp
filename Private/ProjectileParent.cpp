// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileParent.h"
#include "PaperFlipbookComponent.h"
#include "Plateformer2DCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileParent::AProjectileParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComponent;

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbook"));
	PaperFlipbookComponent->SetupAttachment(SceneComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetupAttachment(SceneComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

}

// Called when the game starts or when spawned
void AProjectileParent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlateformer2DCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if (SphereComponent)
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileParent::SphereOverlaped);
	}
}

// Called every frame
void AProjectileParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileParent::SphereOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PlayerCharacter && OtherActor == PlayerCharacter)
	{
		PlayerCharacter->TakeDamage(DamageAmount, FDamageEvent(), nullptr, nullptr);
	}

	Destroy();
}

