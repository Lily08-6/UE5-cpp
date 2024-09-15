// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySimple.h"
#include "Plateformer2DCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemySimple::AEnemySimple()
{
}

void AEnemySimple::BeginPlay()
{
	Super::BeginPlay();

	bEMoveRight = FMath::RandBool();
	AEnemyBase::ToggleFacingDirection();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemySimple::OnHit);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemySimple::OnSphereOverlaped);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemySimple::OnSphereEndOverlap);
}

void AEnemySimple::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
	if (!bAlreadyHit)
	{
		bAlreadyHit = true;
		AEnemySimple::OnCapsuleComponentHit(OtherActor, Hit.Normal);
	}
}

void AEnemySimple::OnCapsuleComponentHit(AActor* OtherActor, FVector HitNormal)
{
	Super::OnCapsuleComponentHit(OtherActor, HitNormal);

	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0))
	{
		if (HitNormal.X != 0.0f)
		{
			bEMoveRight = !bEMoveRight;

			AEnemyBase::ToggleFacingDirection();
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemySimple::ResetHit, 0.2f, false);
		}
	}
}

void AEnemySimple::OnSphereOverlaped(UPrimitiveComponent* OverlapedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlaped(OverlapedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	if (bCanFollowCharacter && OtherActor == PlayerCharacter)
	{
		bFollowingCharacter = true;
	}
}

void AEnemySimple::OnSphereEndOverlap(UPrimitiveComponent* OverlapedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlapedComp, OtherActor, OtherComp, OtherBodyIndex);
	
	if (bCanFollowCharacter && OtherActor == PlayerCharacter)
	{
		bFollowingCharacter = false;
		Move();
	}
}

void AEnemySimple::ResetHit()
{
	bAlreadyHit = false;
}

void AEnemySimple::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Move();
	if (bCanFollowCharacter && bFollowingCharacter)
	{
		FollowCharacter();
	}
}
