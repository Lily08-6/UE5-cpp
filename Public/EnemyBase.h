// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class PLATEFORMER2DGAME_API AEnemyBase : public APaperCharacter
{
	GENERATED_BODY()

public:

	AEnemyBase();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;	

protected:

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
	UPROPERTY(VisibleAnywhere, Category ="Plateformer2D|Actor Component")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category ="Plateformer2D|Actor Component")
	class UDeathComponent* DeathComponent;

	UPROPERTY(VisibleAnywhere, Category ="Plateformer2D|Actor Component")
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Player")
	class APlateformer2DCharacter* PlayerCharacter;

public:

	void ToggleFacingDirection();

#pragma region MOVEMENT

	void Move();
	void FollowCharacter();

#pragma endregion

	virtual void OnCapsuleComponentHit(AActor* OtherActor, FVector HitNormal){}

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit){}
	
	virtual void OnSphereOverlaped(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){}

	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlapedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){}

protected:

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Props")
	bool bEMoveRight = false;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Props")
	bool bFollowingCharacter = false;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Props")
	FVector EWorldDirection = FVector(1.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Props")
	float MaxDistanceBetweenCharacter = 40.f;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Props")
	bool bCanTakeDamage = false;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Props")
	float DefaultDamageAmount = 10.f;

public:
	
	float GetDefaultDamageAmount() const
	{
		return DefaultDamageAmount;
	}

	bool IsCanTakeDamage() const
	{
		return bCanTakeDamage;
	}
};
