// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileParent.generated.h"

UCLASS()
class PLATEFORMER2DGAME_API AProjectileParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileParent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class UPaperFlipbookComponent* PaperFlipbookComponent;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class APlateformer2DCharacter* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category="Plateformer2D|Interaction|Params")
	float DamageAmount = 40.f;

public:

	UFUNCTION(BlueprintCallable, Category = "Plateformer2D")
	void SphereOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
